/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:03:04 by recherra          #+#    #+#             */
/*   Updated: 2025/03/13 15:02:15 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cubed.h"

void	 minimap_calcs(t_all_data *data, t_cu *cu_map)
{
	data->minimap.tile = TILE;

	data->minimap.width = cu_map->map_width * data->minimap.tile;
	data->minimap.height = cu_map->map_height * data->minimap.tile;
}

static int get_player_direction(char c)
{
    if (c == 'N' || c == 'S' || c == 'E' ||  c==  'W')
        return c;
    return 0;
}

void    mini_map(t_all_data *data, t_cu *cu_map, bool first_time)
{
    int i = 0;
    int direction = 0;
    data->player.fov_angle = 60 * to_rad;


    while (cu_map->map[i])
    {
        int j = 0;
        int tile_y = i * data->minimap.tile;
        while (cu_map->map[i][j])
        {
            int tile_x = j * data->minimap.tile;
            if (cu_map->map[i][j] == '1')
                print_square(&data->minimap_img, tile_x, tile_y, data->minimap);
            direction = get_player_direction(cu_map->map[i][j]);
            if (direction)
            {
                data->player.direction = direction;
                if (first_time)
                {
                    data->player.x = tile_x;
                    data->player.y = tile_y;
                }
                print_player(&data->minimap_img, data->player.x, data->player.y, data->minimap);
            }
            j++;
        }
        i++;
    }
}
