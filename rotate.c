/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:48:45 by recherra          #+#    #+#             */
/*   Updated: 2024/10/10 20:48:46 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int fixed_degree(int degree)
{
    degree = degree % 360;
    if (degree < 0)
        return degree + 360;
    return degree;
}

void rotate(t_all_data *data, int direction)
{
    float	cos_theta;
    float	sin_theta;
    float	radian;
    float   delta_x = data->endpoint.x - data->player.x;
    float   delta_y = data->endpoint.y - data->player.y;
    int     degree_to_add = 5 * direction;


    radian = (degree_to_add * to_rad);
    cos_theta = cos(radian);
    sin_theta = sin(radian);
    float x = (delta_x * cos_theta) - (delta_y * sin_theta) + data->player.x;
    float y = (delta_x * sin_theta) + (delta_y * cos_theta ) + data->player.y;
    data->endpoint.x = x;
    data->endpoint.y = y;
    data->player.player_angle_degree = fixed_degree((data->player.player_angle_degree + degree_to_add));
    data->player.player_angle_rad = data->player.player_angle_degree * to_rad;
}