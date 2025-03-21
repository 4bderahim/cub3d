/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:03:04 by recherra          #+#    #+#             */
/*   Updated: 2025/03/19 17:35:18 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void minimap_calcs(t_all_data *data, t_cu *cu_map)
{
    data->minimap.tile = TILE;

    data->minimap.width = cu_map->map_width * data->minimap.tile;
    data->minimap.height = cu_map->map_height * data->minimap.tile;
}

int	position_check(t_all_data *data,  double x, double y, t_cu *map)
{
	if (x >= 0 && x < data->minimap.width
		&& y >= 0 && y < data->minimap.height)
	{
		if (check_wall(data, x, y) == 0
			|| get_player_direction(map->map[(int)(y / data->minimap.tile)][(int)(x / data->minimap.tile)])
			)  
			return 0;
		else if (check_wall(data, x, y) == 1)
			return 1;
	}
	return -1;
}

void	mini_map(t_all_data *data, t_cu *cu_map)
{
	int		i = 0;
	int		j = 0;
	double	starting_x;
	double	starting_y;
	int 	padding = 8;

	starting_y  = data->player.y - padding * data->minimap.tile;
	while (j < data->minimap.tile * (padding * 2))
	{
		starting_x = data->player.x - padding * data->minimap.tile;
		i = 0;
		while (i < data->minimap.tile * (padding * 2))
		{
			if (position_check(data, starting_x, starting_y , cu_map) == 1)
                custom_mlx_pixel_put(&data->game_img, i, j, 0xffffff);
			else if (position_check(data, starting_x, starting_y , cu_map) == 0)
                custom_mlx_pixel_put(&data->game_img, i, j, 0x000000);
			else
                custom_mlx_pixel_put(&data->game_img , i, j, 0x808080);
			i++;
			starting_x++;
		}
		j++;
		starting_y++;
	}
    print_player(&data->game_img, padding * data->minimap.tile, padding * data->minimap.tile);
}

