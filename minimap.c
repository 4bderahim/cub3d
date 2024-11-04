/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:03:04 by recherra          #+#    #+#             */
/*   Updated: 2024/10/10 21:03:05 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cubed.h"

static int check_player(char c)
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
            direction = check_player(cu_map->map[i][j]);
            int tile_x = j * data->minimap.tile;
            if (cu_map->map[i][j] == '1')
                print_square(&data->minimap_img, tile_x, tile_y, data->minimap);
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