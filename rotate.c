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

void rotate(t_all_data *data, int direction)
{
    float	cos_theta;
    float	sin_theta;
    float	radian;
    float   delta_x = data->endpoint.x - data->player.x;
    float   delta_y = data->endpoint.y - data->player.y;


    radian = (10 * to_deg) * direction;
    cos_theta = cos(radian);
    sin_theta = sin(radian);
    float x = (delta_x * cos_theta) - (delta_y * sin_theta) + data->player.x;
    float y = (delta_x * sin_theta) + (delta_y * cos_theta ) + data->player.y;
    data->endpoint.x = x;
    data->endpoint.y = y;
    data->player.player_angle_rad += radian;
}