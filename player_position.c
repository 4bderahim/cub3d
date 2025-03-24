/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:11:21 by recherra          #+#    #+#             */
/*   Updated: 2025/03/24 16:02:00 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	get_player_direction(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (c);
	return (0);
}

static void	set_player_infos(t_all_data *data, int direction, int x, int y)
{
	if (direction)
	{
		data->player.direction = direction;
		data->player.x = x;
		data->player.y = y;
	}
}

void	player_position(t_all_data *data, t_cu *cu_map)
{
	int	i;
	int	j;
	int	tile_x;
	int	tile_y;
	int	direction;

	i = 0;
	j = 0;
	tile_x = 0;
	tile_y = 0;
	direction = 0;
	data->player.fov_angle = 60 * to_rad;
	while (cu_map->map[i])
	{
		tile_y = i * data->minimap.tile;
		j = 0;
		while (cu_map->map[i][j])
		{
			tile_x = j * data->minimap.tile;
			direction = get_player_direction(cu_map->map[i][j]);
			set_player_infos(data, direction, tile_x, tile_y);
			j++;
		}
		i++;
	}
}
