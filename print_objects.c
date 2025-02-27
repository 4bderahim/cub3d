/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:01:23 by recherra          #+#    #+#             */
/*   Updated: 2025/02/17 17:00:25 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	print_player(t_data *minimap_img, int tile_x, int tile_y,
		t_minimap minimap)
{
	int	dot;
	int	i;
	int	j;

	(void)minimap;
	dot = 4;
	i = 0;
	while (i < dot)
	{
		j = 0;
		while (j < dot)
		{
			custom_mlx_pixel_put(minimap_img, tile_x + i, tile_y + j, 0xFF0000);
			j++;
		}
		i++;
	}
}

void	print_square(t_data *minimap_img, int tile_x, int tile_y,
		t_minimap minimap)
{
	int	tile;
	int	i;
	int	j;

	tile = minimap.tile;
	i = 0;
	while (i < tile - 1)
	{
		j = 0;
		while (j < tile - 1)
		{
			custom_mlx_pixel_put(minimap_img, tile_x + i, tile_y + j, 0xffffff);
			j++;
		}
		i++;
	}
}
