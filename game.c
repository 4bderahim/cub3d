/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 21:09:34 by recherra          #+#    #+#             */
/*   Updated: 2025/03/24 16:02:00 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	game(t_all_data *data)
{
	int		i;
	float	sanitized_distance;
	float	wall_height;

	celine_and_floor(data);
	i = 0;
	while (i < N_RAYS)
	{
		sanitized_distance = data->rays[i].distance
			* cos(data->rays[i].ray_angle - data->player.player_angle_rad);
		wall_height = (data->minimap.tile * HEIGHT * 1.4) / sanitized_distance;
		print_wall(data, wall_height, i, (HEIGHT / 2) - (wall_height / 2));
		i++;
	}
}
