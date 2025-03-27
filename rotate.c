/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:48:45 by recherra          #+#    #+#             */
/*   Updated: 2025/03/27 22:25:46 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	rotate(t_all_data *data, int direction)
{
	int	factor;
	int	to_add;

	factor = 4;
	to_add = factor * direction;
	data->player.player_angle_degree += to_add;
	data->player.player_angle_rad = data->player.player_angle_degree * to_rad;
}
