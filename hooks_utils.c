/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:54:12 by recherra          #+#    #+#             */
/*   Updated: 2025/03/26 18:12:58 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

#define MOVE_FACTOR 4

static int	check_collision(t_all_data *data, int pos_x, int pos_y)
{
	// if (data->cu_map->map[pos_y][pos_x] == '1' || 
	// 	data->cu_map->map[pos_y - 1][pos_x] == '1' || 
	// 	data->cu_map->map[pos_y][pos_x - 1] == '1'  || 
	// 	data->cu_map->map[pos_y + 1][pos_x] == '1' ||
	// 	data->cu_map->map[pos_y ][pos_x+1] == '1')
	if (data->cu_map->map[pos_y][pos_x] == '1') 
	{
		return 1;
	}
	// || // data->cu_map->map[pos_y - 1][pos_x] == '1' || 
		// data->cu_map->map[pos_y][pos_x - 1] == '1' )
	return 0;	
}

static int	get_position_x(t_all_data *data)
{
	return (data->player.x / data->minimap.tile);
}

static int	get_position_y(t_all_data *data)
{
	return (data->player.y / data->minimap.tile);
}

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
	data->player.x += to_add_x;
	data->player.y += to_add_y;
	if (check_collision(data, get_position_x(data), get_position_y(data)))
	{
		data->player.x -= to_add_x;
		data->player.y -= to_add_y;
		return ;
	}
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
	data->player.x += to_add_x;
	data->player.y += to_add_y;
	if (check_collision(data, get_position_x(data), get_position_y(data)))
	{
		data->player.x -= to_add_x;
		data->player.y -= to_add_y;
		return ;
	}
}
