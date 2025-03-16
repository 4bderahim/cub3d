/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:54:32 by recherra          #+#    #+#             */
/*   Updated: 2025/03/16 15:58:37 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	vertical_hit(int i, t_rays_utils vertical, t_all_data *data)
{
	data->rays[i].verical_hit = 1;
	data->rays[i].wall_x = vertical.x_hit;
	data->rays[i].wall_y = vertical.y_hit;
	data->rays[i].distance = vertical.distance;
}

void	horizontal_hit(int i, t_rays_utils horizontal, t_all_data *data)
{
	data->rays[i].verical_hit = 0;
	data->rays[i].wall_x = horizontal.x_hit;
	data->rays[i].wall_y = horizontal.y_hit;
	data->rays[i].distance = horizontal.distance;
}

void	cast_ray(float ray_angle, int i, t_all_data *data)
{
	t_direction		direction;
	t_rays_utils	horizontal;
	t_rays_utils	vertical;

	ray_angle = angle_fix(ray_angle);
	set_direction(&direction, ray_angle);
	horizontal_intersection(data, direction, &horizontal, ray_angle);
	vertical_intersection(data, direction, &vertical, ray_angle);
	horizontal.distance = calculate__(data->player.x, data->player.y,
			horizontal.x_hit, horizontal.y_hit);
	vertical.distance = calculate__(data->player.x, data->player.y,
			vertical.x_hit, vertical.y_hit);
	if (vertical.distance < horizontal.distance)
		vertical_hit(i, vertical, data);
	else
		horizontal_hit(i, horizontal, data);
	data->rays[i].direction = direction;
	data->rays[i].ray_angle = ray_angle;
}

void	cast_rays(t_all_data *data)
{
	int		i;
	float	ray_angle;
	float	angle_factor;

	i = 0;
	ray_angle = data->player.player_angle_rad - (data->player.fov_angle / 2);
	angle_factor = data->player.fov_angle / N_RAYS;
	while (i < N_RAYS)
	{
		cast_ray(ray_angle, i++, data);
		ray_angle += angle_factor;
	}
}
