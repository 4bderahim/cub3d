/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 21:09:34 by recherra          #+#    #+#             */
/*   Updated: 2025/03/26 00:21:08 by recherra         ###   ########.fr       */
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
		wall_height = (data->minimap.tile * HEIGHT * 1.5) / fmax(sanitized_distance, 1);
		print_wall(data, wall_height, i, (HEIGHT / 2) - (wall_height / 2));
		i++;
	}
}
