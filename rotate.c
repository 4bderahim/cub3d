/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:48:45 by recherra          #+#    #+#             */
/*   Updated: 2025/02/18 16:36:07 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	fixed_degree(int degree)
{
	degree = degree % 360;
	if (degree < 0)
		return (degree + 360);
	return (degree);
}

void	rotate(t_all_data *data, int direction)
{
	t_rotation	u;
	int			*ref;

	ref = &data->player.player_angle_degree;
	u.delta_x = data->endpoint.x - data->player.x;
	u.delta_y = data->endpoint.y - data->player.y;
	u.degree_to_add = 5 * direction;
	u.radian = (u.degree_to_add * to_rad);
	u.cos_theta = cos(u.radian);
	u.sin_theta = sin(u.radian);
	u.x = (u.delta_x * u.cos_theta) - (u.delta_y * u.sin_theta)
		+ data->player.x;
	u.y = (u.delta_x * u.sin_theta) + (u.delta_y * u.cos_theta)
		+ data->player.y;
	data->endpoint.x = u.x;
	data->endpoint.y = u.y;
	*ref = fixed_degree((*ref + u.degree_to_add));
	data->player.player_angle_rad = *ref * to_rad;
}
