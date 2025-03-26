/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:54:12 by recherra          #+#    #+#             */
/*   Updated: 2025/03/26 20:44:41 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

#define MOVE_FACTOR 4




// bool	check_width(t_all_data *data, int x, int y)
// {
// 	int	i;

// 	i = -5;
// 	while (i <= 5)
// 	{
// 		if (y / TILE >= 0 && y / TILE < (data ->minimap.height / TILE)
// 			&& (x + i) / TILE >= 0 && (x + i) / TILE < (data->minimap.width / TILE))
// 		{
// 			if (data->cu_map->map[y / TILE][(x + i) / TILE] == '1')
// 				return (false);
// 		}
// 		i++;
// 	}
// 	return (true);
// }



static int	check(t_all_data *data, double x, double y)
{
	if (data->cu_map->map[(int)(y / data->minimap.tile)][(int)(x
			/ data->minimap.tile)] == '1')
	{
		return (1);
	}
	return (0);
}

static int	check_collision(t_all_data *data, double x, double y)
{
	int i = -3;
	while (i <= 3)
	{	
		if (x >= 0 && x < data->minimap.width && y >= 0 && y < data->minimap.height)
		{
			if (check(data, x, y + i))
				return (1);
		}
		i++;
	}

	i = -3;
	while (i <= 3)
	{	
		if (x >= 0 && x < data->minimap.width && y >= 0 && y < data->minimap.height)
		{
			if (check(data, x + i, y))
				return (1);
		}
		i++;
	}
	
	return 0;
}

void	up_down(t_all_data *data, int direction)
{
	double	factor_x;
	double	factor_y;
	double	to_add_x;
	double	to_add_y;

	factor_x = cos(data->player.player_angle_rad) * MOVE_FACTOR;
	factor_y = sin(data->player.player_angle_rad) * MOVE_FACTOR;
	to_add_x = factor_x * direction;
	to_add_y = factor_y * direction;
	if (check_collision(data, data->player.x + to_add_x, data->player.y + to_add_y))
		return ;
	data->player.x += to_add_x;
	data->player.y += to_add_y;
}

void	right_left(t_all_data *data, int direction)
{
	double	factor_x;
	double	factor_y;
	double	to_add_x;
	double	to_add_y;
	double	angle;

	angle = data->player.player_angle_rad - (90 * to_rad);
	factor_x = cos(angle) * MOVE_FACTOR;
	factor_y = sin(angle) * MOVE_FACTOR;
	to_add_x = factor_x * direction;
	to_add_y = factor_y * direction;
	if (check_collision(data, data->player.x + to_add_x, data->player.y + to_add_y))
		return ;
	data->player.x += to_add_x;
	data->player.y += to_add_y;
}
