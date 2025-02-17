/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:38:01 by recherra          #+#    #+#             */
/*   Updated: 2025/02/17 16:59:26 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	north(t_all_data *data)
{
	data->endpoint.x = data->player.x;
	data->endpoint.y = 0;
	data->player.player_angle_rad = 90 * to_rad;
	data->player.player_angle_degree = 90;
}

void	south(t_all_data *data)
{
	data->endpoint.x = data->player.x;
	data->endpoint.y = data->minimap.height;
	data->player.player_angle_rad = 270 * to_rad;
	data->player.player_angle_degree = 270;
}

void	east(t_all_data *data)
{
	data->endpoint.x = data->minimap.width;
	data->endpoint.y = data->player.y;
	data->player.player_angle_rad = 180 * to_rad;
	data->player.player_angle_degree = 180;
}

void	west(t_all_data *data)
{
	data->endpoint.x = 0;
	data->endpoint.y = data->player.y;
	data->player.player_angle_rad = 0 * to_rad;
	data->player.player_angle_degree = 0;
}

void	initial_endpoint(t_all_data *data)
{
	int	direction;

	direction = data->player.direction;
	if (direction == 'N')
		north(data);
	else if (direction == 'S')
		south(data);
	else if (direction == 'E')
		east(data);
	else if (direction == 'W')
		west(data);
}
