/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:50:48 by recherra          #+#    #+#             */
/*   Updated: 2025/03/27 22:27:02 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	process_data(t_dda_data *dda, t_coords *start, t_coords *end)
{
	dda->dx = end->x - start->x;
	dda->dy = end->y - start->y;
	dda->steps = 0;
	if (fabs(dda->dx) >= fabs(dda->dy))
		dda->steps = fabs(dda->dx);
	else
		dda->steps = fabs(dda->dy);
	dda->factor_x = dda->dx / dda->steps;
	dda->factor_y = dda->dy / dda->steps;
	dda->increment_x = start->x;
	dda->increment_y = start->y;
}

static void	ray_dda(t_all_data *data, t_coords *start, t_coords *end)
{
	int			i;
	t_dda_data	dda;

	i = 0;
	process_data(&dda, start, end);
	while (i < dda.steps)
	{
		custom_mlx_pixel_put(&data->game_img, dda.increment_x, dda.increment_y,
			0xFFFFFFFF);
		dda.increment_x += dda.factor_x;
		dda.increment_y += dda.factor_y;
		i++;
	}
}

void	dda(t_all_data *data, int padding)
{
	t_coords	start;
	t_coords	end;
	float		ray_angle;

	start.x = data->minimap.tile * padding + 2;
	start.y = start.x;
	ray_angle = data->player.player_angle_rad;
	end.x = start.x - cos(ray_angle) * 25;
	end.y = start.y - sin(ray_angle) * 25;
	ray_dda(data, &start, &end);
}
