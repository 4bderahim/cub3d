/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 21:07:40 by recherra          #+#    #+#             */
/*   Updated: 2025/03/13 15:21:44 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	render__rays(t_all_data *data)
{
	int	i;

	i = 0;
	while (i < N_RAYS)
	{
		ray_dda(data, data->rays[i].wall_x, data->rays[i].wall_y);
		custom_mlx_pixel_put(&data->minimap_img, data->rays[i].wall_x,
			data->rays[i].wall_y, 0xFF0000);
		custom_mlx_pixel_put(&data->minimap_img, data->rays[i].wall_x + 1,
			data->rays[i].wall_y + 1, 0xFF0000);
		i++;
	}
}

void	init_rays(t_all_data *data)
{
	data->rays = malloc(sizeof(t_ray) * N_RAYS);
	if (!data->rays)
		exit(1);
}
