/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_inters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:41:44 by recherra          #+#    #+#             */
/*   Updated: 2025/02/18 16:30:50 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	check_vertical_intersection(t_all_data *data,
		t_rays_utils *vertical, t_direction direction)
{
	float	x_check;
	float	y_check;

	while (vertical->x_hit > 0 && vertical->x_hit < data->minimap.width
		&& vertical->y_hit > 0 && vertical->y_hit < data->minimap.height)
	{
		x_check = vertical->x_hit;
		if (direction.left)
			x_check = vertical->x_hit - 1;
		y_check = vertical->y_hit;
		if (data->cu_map->map[(int)(y_check / data->minimap.tile)][(int)(x_check
				/ data->minimap.tile)] == '1')
			break ;
		vertical->x_hit += vertical->x_step;
		vertical->y_hit += vertical->y_step;
	}
}

void	vertical_intersection(t_all_data *data, t_direction direction,
		t_rays_utils *vertical, float ray_angle)
{
	vertical->x_hit = (int)(data->player.x / data->minimap.tile)
		* data->minimap.tile;
	if (direction.right)
		vertical->x_hit += data->minimap.tile;
	vertical->y_hit = data->player.y + ((vertical->x_hit - data->player.x)
			* tan(ray_angle));
	vertical->x_step = data->minimap.tile;
	if (direction.left)
		vertical->x_step *= -1;
	vertical->y_step = data->minimap.tile * tan(ray_angle);
	if (direction.up && vertical->y_step > 0)
		vertical->y_step *= -1;
	if (direction.down && vertical->y_step < 0)
		vertical->y_step *= -1;
	check_vertical_intersection(data, vertical, direction);
}
