/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   celine_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:50:31 by recherra          #+#    #+#             */
/*   Updated: 2025/03/24 16:02:01 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	celine_and_floor(t_all_data *data)
{
	int	celine_color;
	int	floor_color;
	int	i;
	int	j;

	celine_color = create_rgb(data->cu_map->cr, data->cu_map->cg,
			data->cu_map->cb);
	floor_color = create_rgb(data->cu_map->fr, data->cu_map->fg,
			data->cu_map->fb);
	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT / 2)
			custom_mlx_pixel_put(&data->game_img, i, j++, celine_color);
		i++;
	}
	i = 0;
	while (i < WIDTH)
	{
		j = HEIGHT / 2;
		while (j < HEIGHT)
			custom_mlx_pixel_put(&data->game_img, i, j++, floor_color);
		i++;
	}
}
