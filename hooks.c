/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resherra <resherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:51:18 by recherra          #+#    #+#             */
/*   Updated: 2024/10/24 16:28:17 by resherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

#define MOVE_FACTOR 3

int check_collision(t_all_data *data, int pos_x, int pos_y)
{
    return data->cu_map->map[pos_y][pos_x] == '1';
}
int get_position_x(t_all_data *data, float offset)
{
    return (data->player.x + offset) / data->minimap.tile;
}

int get_position_y(t_all_data *data, float offset)
{
    return (data->player.y + offset) / data->minimap.tile;
}

void up_down(t_all_data *data, int direction)
{
    float angle = data->player.player_angle_rad;
    float factor_x = cos(angle) * MOVE_FACTOR;
    float factor_y = sin(angle) * MOVE_FACTOR;

    data->player.x += factor_x * direction;
    data->player.y += factor_y * direction;

    int position_x = get_position_x(data, factor_x * direction);
    int position_y = get_position_y(data, factor_y * direction);

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
    float factor_x = cos(data->player.player_angle_rad - (90 * to_rad)) * MOVE_FACTOR;
    float factor_y = sin(data->player.player_angle_rad - (90 * to_rad)) * MOVE_FACTOR;

    data->player.x += factor_x * direction;
    data->player.y += factor_y * direction;

    int position_x = get_position_x(data, factor_x * direction);
    int position_y = get_position_y(data, factor_y * direction);
    if (check_collision(data, position_x, position_y))
    {
        data->player.x -= factor_x * direction;
        data->player.y -= factor_y * direction;
        return;
    }
    data->endpoint.x += factor_x * direction;
    data->endpoint.y += factor_y * direction;
}

void re_position_player(int keycode, t_all_data *data)
{
    if (keycode == WK)
        up_down(data, -1);
    if (keycode == SK)
        up_down(data, 1);
    if (keycode == AK)
        right_left(data, -1);
    if (keycode == DK)
        right_left(data, 1);
}

void re_pov(int keycode, t_all_data *data)
{
    if (keycode == RA)
        rotate(data, 1);
    if (keycode == LA)
        rotate(data, -1);
}