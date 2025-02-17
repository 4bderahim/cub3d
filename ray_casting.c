/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:54:32 by recherra          #+#    #+#             */
/*   Updated: 2025/02/17 21:14:22 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

float	angle_fix(float angle)
{
	angle = remainder(angle, M_PI * 2);
	if (angle < 0)
		angle = (M_PI * 2) + angle;
	return (angle);
}

float	calculate__(float px, float py, float px_hit, float py_hit)
{
	return (sqrt(pow(px_hit - px, 2) + pow(py_hit - py, 2)));
}

void	set_direction(t_direction *direction, float ray_angle)
{
	direction->up = 0;
	direction->left = 0;
	if (ray_angle > 0 && ray_angle < M_PI)
		direction->up = 1;
	direction->down = !(direction->up);
	if (ray_angle < (M_PI / 2) || ray_angle > (M_PI + (M_PI / 2)))
		direction->left = 1;
	direction->right = !direction->left;
}

void	horizontal_intersection(t_all_data *data, t_direction direction,
		t_rays_utils *horizontal, float ray_angle)
{
	float	x_check;
	float	y_check;

	x_check = 0;
	y_check = 0;
	horizontal->y_hit = (int)(data->player.y / data->minimap.tile)
		* data->minimap.tile;
	if (direction.down)
		horizontal->y_hit += data->minimap.tile;
	// x
	horizontal->x_hit = data->player.x + ((horizontal->y_hit - data->player.y)
			/ tan(ray_angle));
	// horizonal x & y steps
	// y
	horizontal->y_step = data->minimap.tile;
	if (direction.up)
		horizontal->y_step *= -1;
	// x
	horizontal->x_step = data->minimap.tile / tan(ray_angle);
	if (direction.left && horizontal->x_step > 0)
		horizontal->x_step *= -1;
	if (direction.right && horizontal->x_step < 0)
		horizontal->x_step *= -1;
	// search for intersection
	while (horizontal->x_hit > 0 && horizontal->x_hit < data->minimap.width
		&& horizontal->y_hit > 0 && horizontal->y_hit < data->minimap.height)
	{
		x_check = horizontal->x_hit;
		y_check = horizontal->y_hit;
		if (direction.up)
			y_check = horizontal->y_hit - 1;
		if (data->cu_map->map[(int)(y_check / data->minimap.tile)][(int)(x_check
				/ data->minimap.tile)] == '1')
			break ;
		horizontal->x_hit += horizontal->x_step;
		horizontal->y_hit += horizontal->y_step;
	}
}

void	vertical_intersection(t_all_data *data, t_direction direction,
		t_rays_utils *vertical, float ray_angle)
{
	float	x_check;
	float	y_check;

	x_check = 0;
	y_check = 0;
	// intersection
	// x
	vertical->x_hit = (int)(data->player.x / data->minimap.tile)
		* data->minimap.tile;
	if (direction.right)
		vertical->x_hit += data->minimap.tile;
	// y
	vertical->y_hit = data->player.y + ((vertical->x_hit - data->player.x)
			* tan(ray_angle));
	// vertical x & y steps
	// x
	vertical->x_step = data->minimap.tile;
	if (direction.left)
		vertical->x_step *= -1;
	// y
	vertical->y_step = data->minimap.tile * tan(ray_angle);
	if (direction.up && vertical->y_step > 0)
		vertical->y_step *= -1;
	if (direction.down && vertical->y_step < 0)
		vertical->y_step *= -1;
	// search for intersection
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

void	cast_ray(float ray_angle, int i, t_all_data *data)
{
	t_direction		direction;
	t_rays_utils	horizontal;
	t_rays_utils	vertical;

	ray_angle = angle_fix(ray_angle);
	// set ray direction
	set_direction(&direction, ray_angle);
	horizontal_intersection(data, direction, &horizontal, ray_angle);
	vertical_intersection(data, direction, &vertical, ray_angle);
	// calculate and compare distances
	horizontal.distance = calculate__(data->player.x, data->player.y,
			horizontal.x_hit, horizontal.y_hit);
	vertical.distance = calculate__(data->player.x, data->player.y,
			vertical.x_hit, vertical.y_hit);
	if (vertical.distance < horizontal.distance)
	{
		data->rays[i].verical_hit = 1;
		data->rays[i].wall_x = vertical.x_hit;
		data->rays[i].wall_y = vertical.y_hit;
		data->rays[i].distance = vertical.distance;
	}
	else
	{
		data->rays[i].verical_hit = 0;
		data->rays[i].wall_x = horizontal.x_hit;
		data->rays[i].wall_y = horizontal.y_hit;
		data->rays[i].distance = horizontal.distance;
	}
	data->rays[i].ray_left = direction.left;
	data->rays[i].ray_right = direction.right;
	data->rays[i].ray_down = direction.down;
	data->rays[i].ray_up = direction.up;
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
