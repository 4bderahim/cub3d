/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:45:20 by recherra          #+#    #+#             */
/*   Updated: 2025/02/17 21:14:39 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	mlx_get_color_at(t_data data, int x, int y, unsigned int *color)
{
	*color = *(unsigned int *)(data.addr + (y * data.line_length) + (x
				* (data.bits_per_pixel / 8)));
}

static double	get_offset_x(t_all_data *data, int starting_x,
		int texture_width)
{
	double	offset_x;

	offset_x = 0;
	if (!data->rays[starting_x].verical_hit)
	{
		offset_x = fmod(data->rays[starting_x].wall_x, data->minimap.tile);
		offset_x *= texture_width / data->minimap.tile;
	}
	else
	{
		offset_x = fmod(data->rays[starting_x].wall_y, data->minimap.tile);
		offset_x *= texture_width / data->minimap.tile;
	}
	return (offset_x);
}

static int	get_texture(t_ray ray)
{
	if (ray.verical_hit == 0)
	{
		if (ray.ray_up)
			return (3);
		else if (ray.ray_down)
			return (0);
	}
	else
	{
		if (ray.ray_right)
			return (2);
		else if (ray.ray_left)
			return (1);
	}
	return (0);
}

void	print_wall(t_all_data *data, float wall_height, int starting_x,
		int starting_y)
{
	t_wall_data	wall_d;
	int			i;

	i = 0;
	wall_d.texture_num = get_texture(data->rays[starting_x]);
	wall_d.texture_width = data->news[wall_d.texture_num]->width;
	wall_d.texture_height = data->news[wall_d.texture_num]->height;
	wall_d.offset_x = get_offset_x(data, starting_x, wall_d.texture_width);
	while (i < wall_height)
	{
		wall_d.x = starting_x;
		wall_d.y = starting_y + i;
		wall_d.distance_from_top = wall_d.y - starting_y;
		wall_d.offset_y = wall_d.distance_from_top * wall_d.texture_height
			/ wall_height;
		mlx_get_color_at(data->news[wall_d.texture_num]->data, wall_d.offset_x,
			wall_d.offset_y, &wall_d.color);
		if (wall_d.x > 0 && wall_d.x < WIDTH && wall_d.y > 0
			&& wall_d.y < HEIGHT)
			custom_mlx_pixel_put(&data->game_img, wall_d.x, wall_d.y,
				wall_d.color);
		i++;
	}
}
