/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:54:12 by recherra          #+#    #+#             */
/*   Updated: 2025/03/27 22:32:16 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	up_down(t_all_data *data, int direction)
{
	float	factor_x;
	float	factor_y;
	float	to_add_x;
	float	to_add_y;

	factor_x = cos(data->player.player_angle_rad) * MOVE_FACTOR;
	factor_y = sin(data->player.player_angle_rad) * MOVE_FACTOR;
	to_add_x = factor_x * direction;
	to_add_y = factor_y * direction;
	if (check_collision(data, data->player.x + to_add_x, data->player.y
			+ to_add_y))
		return ;
	data->player.x += to_add_x;
	data->player.y += to_add_y;
}

void	right_left(t_all_data *data, int direction)
{
	float	factor_x;
	float	factor_y;
	float	to_add_x;
	float	to_add_y;
	float	angle;

	angle = data->player.player_angle_rad - (90 * to_rad);
	factor_x = cos(angle) * MOVE_FACTOR;
	factor_y = sin(angle) * MOVE_FACTOR;
	to_add_x = factor_x * direction;
	to_add_y = factor_y * direction;
	if (check_collision(data, data->player.x + to_add_x, data->player.y
			+ to_add_y))
		return ;
	data->player.x += to_add_x;
	data->player.y += to_add_y;
}
