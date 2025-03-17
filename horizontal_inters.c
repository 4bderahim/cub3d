/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_inters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:41:34 by recherra          #+#    #+#             */
/*   Updated: 2025/03/17 16:24:26 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"



static void	check_horizontal_intersection(t_all_data *data,
		t_rays_utils *horizontal, t_direction direction)
{
	float	x_check;
	float	y_check;

	while (horizontal->x_hit > 0 && horizontal->x_hit < data->minimap.width
		&& horizontal->y_hit > 0 && horizontal->y_hit < data->minimap.height)
	{
		x_check = horizontal->x_hit;
		y_check = horizontal->y_hit;
		if (direction.up)
			y_check = horizontal->y_hit - 1;
		if (check_wall(data, x_check, y_check))
			break;
		horizontal->x_hit += horizontal->x_step;
		horizontal->y_hit += horizontal->y_step;
	}
}

void	horizontal_intersection(t_all_data *data, t_direction direction,
		t_rays_utils *horizontal, float ray_angle)
{
	horizontal->y_hit = (int)(data->player.y / data->minimap.tile) 
		* data->minimap.tile;
	if (direction.down)
		horizontal->y_hit += data->minimap.tile;
	horizontal->triangle.opposite = horizontal->y_hit - data->player.y;
	horizontal->x_hit = data->player.x + (horizontal->triangle.opposite
			/ tan(ray_angle));
	horizontal->y_step = data->minimap.tile;
	if (direction.up)
		horizontal->y_step *= -1;
	horizontal->x_step = data->minimap.tile / tan(ray_angle);
	if (direction.left && horizontal->x_step > 0)
		horizontal->x_step *= -1;
	else if (direction.right && horizontal->x_step < 0)
		horizontal->x_step *= -1;
	check_horizontal_intersection(data, horizontal, direction);
}
