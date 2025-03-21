/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:54:12 by recherra          #+#    #+#             */
/*   Updated: 2025/02/17 16:58:25 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

#define MOVE_FACTOR 1.5

static int check_collision(t_all_data *data, int pos_x, int pos_y)
{
    return (data->cu_map->map[pos_y][pos_x] == '1');
}

static int get_position_x(t_all_data *data, float offset)
{
    return ((data->player.x + offset) / data->minimap.tile);
}

static int get_position_y(t_all_data *data, float offset)
{
    return ((data->player.y + offset) / data->minimap.tile);
}

void up_down(t_all_data *data, int direction)
{
    float angle;
    float factor_x;
    float factor_y;
    int position_x;
    int position_y;

    angle = data->player.player_angle_rad;
    factor_x = cos(angle) * MOVE_FACTOR;
    factor_y = sin(angle) * MOVE_FACTOR;
    data->player.x += factor_x * direction;
    data->player.y += factor_y * direction;
    position_x = get_position_x(data, factor_x * direction);
    position_y = get_position_y(data, factor_y * direction);
    if (check_collision(data, position_x, position_y))
    {
        data->player.x -= factor_x * direction;
        data->player.y -= factor_y * direction;
        return;
    }
    data->endpoint.x += factor_x * direction;
    data->endpoint.y += factor_y * direction;
}

void right_left(t_all_data *data, int direction)
{
    float factor_x;
    float factor_y;
    int position_x;
    int position_y;

    factor_x = cos(data->player.player_angle_rad - (90 * to_rad)) * MOVE_FACTOR;
    factor_y = sin(data->player.player_angle_rad - (90 * to_rad)) * MOVE_FACTOR;
    data->player.x += factor_x * direction;
    data->player.y += factor_y * direction;
    position_x = get_position_x(data, factor_x * direction);
    position_y = get_position_y(data, factor_y * direction);
    if (check_collision(data, position_x, position_y))
    {
        data->player.x -= factor_x * direction;
        data->player.y -= factor_y * direction;
        return;
    }
    data->endpoint.x += factor_x * direction;
    data->endpoint.y += factor_y * direction;
}
