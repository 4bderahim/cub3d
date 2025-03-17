/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:03:04 by recherra          #+#    #+#             */
/*   Updated: 2025/03/17 22:23:30 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void minimap_calcs(t_all_data *data, t_cu *cu_map)
{
    data->minimap.tile = TILE;

    data->minimap.width = cu_map->map_width * data->minimap.tile;
    data->minimap.height = cu_map->map_height * data->minimap.tile;
}



// void mini_map(t_all_data *data, t_cu *cu_map)
// {
//     // int i = 0;

//     // while (cu_map->map[i])
//     // {
//     //     int j = 0;
//     //     int tile_y = i * data->minimap.tile;
//     //     while (cu_map->map[i][j])
//     //     {
//     //         int tile_x = j * data->minimap.tile;
//     //         if (cu_map->map[i][j] == '1')
//     //             print_square(&data->minimap_img, tile_x, tile_y, data->minimap);
//     //         j++;
//     //     }
//     //     i++;
//     // }
//     // print_player(&data->minimap_img, data->player.x, data->player.y, data->minimap);
// }

int	space_or_wall(double x, double y, t_cu *map)
{
	if (x >= 0 && x < (map->map_width * TILE)
		&& y >= 0 && y < (map->map_height * TILE))
	{
		if (map->map[(int)(y / TILE)][(int)(x / TILE)] == '0'
			|| ft_strchr("NSEW", map->map[(int)(y /
				TILE)][(int)(x / TILE)]))
			return (1);
		else if (map->map[(int)(y / TILE)][(int)(x / TILE)] == '1')
			return (2);
	}
	return (0);
}

void	mini_map(t_all_data *data, t_cu *cu_map)
{
	double	x;
	double	y;
	int		i;
	int		j;

	j = -1;
	y = data->player.y  - 5 * TILE;
	while (++j < TILE * 10)
	{
		x = data->player.x - 5 * TILE;
		i = -1;
		while (++i < TILE * 10)
		{
			if (space_or_wall(x, y, cu_map) == 2)
            {  
                custom_mlx_pixel_put(&data->minimap_img, i, j, 0xff0000);
				// mlx_put_pixel(data->ft_3d, i, j, get_rgba(0, 0, 0, 255));

            }
			else if (space_or_wall(x, y, cu_map) == 1)
            {
                                custom_mlx_pixel_put(&data->minimap_img, i, j, 0xffff00);

				// mlx_put_pixel(data->ft_3d, i, j, get_rgba(246, 230, 203, 255));
                
            }
			else
            {
                                                custom_mlx_pixel_put(&data->minimap_img, i, j, 0xffffff);
				// mlx_put_pixel(data->ft_3d, i, j, get_rgba(100, 100, 100, 255));
                
            }
			x++;
		}
		y++;
	}
    //player
}