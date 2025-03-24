/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:03:04 by recherra          #+#    #+#             */
/*   Updated: 2025/03/24 22:20:17 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

void	minimap_calcs(t_all_data *data, t_cu *cu_map)
{
	data->minimap.tile = TILE;
	data->minimap.width = cu_map->map_width * data->minimap.tile;
	data->minimap.height = cu_map->map_height * data->minimap.tile;
}

static int	position_check(t_all_data *data, double x, double y, t_cu *map)
{
	if (x >= 0 && x < data->minimap.width && y >= 0 && y < data->minimap.height)
	{
		if (check_wall(data, x, y) == 0 || get_player_direction(map->map[(int)(y
					/ data->minimap.tile)][(int)(x / data->minimap.tile)]))
			return (0);
		else if (check_wall(data, x, y) == 1)
			return (1);
	}
	return (-1);
}

static void	check_and_draw(t_all_data *data, t_minimap_utils utils)
{
	if (position_check(data, utils.starting_x, utils.starting_y,
			data->cu_map) == 1)
		custom_mlx_pixel_put(&data->game_img, utils.i, utils.j, 0xffffff);
	else if (position_check(data, utils.starting_x, utils.starting_y,
			data->cu_map) == 0)
		custom_mlx_pixel_put(&data->game_img, utils.i, utils.j, 0x000000);
	else
		custom_mlx_pixel_put(&data->game_img, utils.i, utils.j, 0x808080);
}

void	mini_map(t_all_data *data)
{
	t_minimap_utils	utils;

	utils.i = 0;
	utils.j = 0;
	utils.padding = 8;
	utils.starting_y = data->player.y - utils.padding * data->minimap.tile;
	while (utils.j < data->minimap.tile * (utils.padding * 2))
	{
		utils.starting_x = data->player.x - utils.padding * data->minimap.tile;
		utils.i = 0;
		while (utils.i < data->minimap.tile * (utils.padding * 2))
		{
			check_and_draw(data, utils);
			utils.i++;
			utils.starting_x++;
		}
		utils.j++;
		utils.starting_y++;
	}
	print_player(&data->game_img, utils.padding * data->minimap.tile,
		utils.padding * data->minimap.tile);
}
