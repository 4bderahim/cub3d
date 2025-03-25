/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:48:45 by recherra          #+#    #+#             */
/*   Updated: 2025/03/25 17:32:54 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	fixed_degree(int degree)
{
	degree = degree % 360;
	if (degree < 0)
		return (degree + 360);
	return (degree);
}

void	rotate(t_all_data *data, int direction, bool from_mouse)
{
	int	factor;
	int	new_angle;
	int	to_add;

	factor = 5;
	if (from_mouse)
		factor = 3;
	to_add = factor * direction;
	new_angle = fixed_degree(data->player.player_angle_degree + to_add);
	data->player.player_angle_degree = new_angle;
	data->player.player_angle_rad = new_angle * to_rad;
}
