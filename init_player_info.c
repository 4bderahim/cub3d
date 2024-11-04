/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_endpoint.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:38:01 by recherra          #+#    #+#             */
/*   Updated: 2024/10/10 21:38:10 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"




void    initial_endpoint(t_all_data *data)
{
    int direction = data->player.direction;
    int player_x = data->player.x;
    int player_y = data->player.y;

    if (direction == 'N')
    {
        data->endpoint.x = player_x;
        data->endpoint.y = 0;
        data->player.player_angle_rad = 90 * to_rad;
        data->player.player_angle_degree = 90;
    }
    else if (direction == 'S')
    {
        data->endpoint.x = player_x;
        data->endpoint.y = data->minimap.height;
        data->player.player_angle_rad = 270 * to_rad;
        data->player.player_angle_degree = 270;

    }
    else if (direction == 'E')
    {
        data->endpoint.x = data->minimap.width;
        data->endpoint.y = player_y;
        data->player.player_angle_rad = 180 * to_rad;
        data->player.player_angle_degree = 180;
    }
    else if (direction == 'W')
    {
        data->endpoint.x = 0;
        data->endpoint.y = player_y;
        data->player.player_angle_rad = 0 * to_rad;
        data->player.player_angle_degree = 0;
    }
}