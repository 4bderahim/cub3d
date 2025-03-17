/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:03:04 by recherra          #+#    #+#             */
/*   Updated: 2025/03/17 17:55:48 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void minimap_calcs(t_all_data *data, t_cu *cu_map)
{
    data->minimap.tile = TILE;

    data->minimap.width = cu_map->map_width * data->minimap.tile;
    data->minimap.height = cu_map->map_height * data->minimap.tile;
}



void mini_map(t_all_data *data, t_cu *cu_map)
{
    // int i = 0;

    // while (cu_map->map[i])
    // {
    //     int j = 0;
    //     int tile_y = i * data->minimap.tile;
    //     while (cu_map->map[i][j])
    //     {
    //         int tile_x = j * data->minimap.tile;
    //         if (cu_map->map[i][j] == '1')
    //             print_square(&data->minimap_img, tile_x, tile_y, data->minimap);
    //         j++;
    //     }
    //     i++;
    // }
    // print_player(&data->minimap_img, data->player.x, data->player.y, data->minimap);

    // int i = 0;
    // int j = 0;
    // int starting_x = data->player.x - 5 * data->minimap.tile;
    // int starting_y = data->player.y - 5 * data->minimap.tile;

    // while (i < 10 * data->minimap.tile)
    // {
    //     j = 0;
    //     while (j < 10 * data->minimap.tile)
    //     {
	// 		int x_check = j + starting_x;
	// 		int y_check = i + starting_y;
	// 		if (x_check > )
			
	// 		if (check_wall(data, j + starting_x, i + starting_y) == 1)
    //         	custom_mlx_pixel_put(&data->minimap_img, j, i, 0xff0000);

    //         // print_player(&data->minimap_img, data->player.x, data->player.y, data->minimap);
    //         j++;
    //     }
    //     i++;
    // }
}
