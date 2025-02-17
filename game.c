/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 21:09:34 by recherra          #+#    #+#             */
/*   Updated: 2025/02/17 21:13:55 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	game(t_all_data *data)
{
	int		i;
	float	to_projection_plan;
	float	sanitized_distance;
	float	wall_height;

	celine_and_floor(data);
	i = 0;
	while (i < N_RAYS)
	{
		to_projection_plan = (WIDTH / 2) / tan(data->player.fov_angle / 2);
		sanitized_distance = data->rays[i].distance
			* cos(data->rays[i].ray_angle - data->player.player_angle_rad);
		wall_height = (data->minimap.tile / sanitized_distance)
			* to_projection_plan;
		print_wall(data, wall_height, i, (HEIGHT / 2) - (wall_height / 2));
		i++;
	}
}
