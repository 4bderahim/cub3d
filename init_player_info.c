/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:38:01 by recherra          #+#    #+#             */
/*   Updated: 2025/03/25 17:19:44 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	north(t_all_data *data)
{
	data->player.player_angle_rad = 90 * to_rad;
	data->player.player_angle_degree = 90;
}

void	south(t_all_data *data)
{
	data->player.player_angle_rad = 270 * to_rad;
	data->player.player_angle_degree = 270;
}

void	east(t_all_data *data)
{
	data->player.player_angle_rad = 180 * to_rad;
	data->player.player_angle_degree = 180;
}

void	west(t_all_data *data)
{
	data->player.player_angle_rad = 0 * to_rad;
	data->player.player_angle_degree = 0;
}

void	initial_angle(t_all_data *data)
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
