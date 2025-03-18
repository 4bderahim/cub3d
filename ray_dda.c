/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:27:49 by recherra          #+#    #+#             */
/*   Updated: 2025/03/18 16:50:34 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	process_data(t_all_data *data, t_dda_data *dda, float ray_x,
		float ray_y)
{
	dda->dx = ray_x - data->player.x;
	dda->dy = ray_y - data->player.y;
	dda->steps = 0;
	if (fabs(dda->dx) >= fabs(dda->dy))
		dda->steps = fabs(dda->dx);
	else
		dda->steps = fabs(dda->dy);
	dda->factor_x = dda->dx / dda->steps;
	dda->factor_y = dda->dy / dda->steps;
	dda->increment_x = data->player.x;
	dda->increment_y = data->player.y;
}

void	ray_dda(t_all_data *data, float ray_x, float ray_y)
{
	int			i;
	t_dda_data	dda;

	i = 0;
	process_data(data, &dda, ray_x, ray_y);
	while (i < dda.steps)
	{
		if (dda.increment_y >= 0 && dda.increment_y <= data->minimap.height
			&& dda.increment_x >= 0 && dda.increment_x <= data->minimap.width)
			custom_mlx_pixel_put(&data->game_img , dda.increment_x,
				dda.increment_y, 0x00FF00);
		dda.increment_x += dda.factor_x;
		dda.increment_y += dda.factor_y;
		i++;
	}
}
