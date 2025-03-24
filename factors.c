/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:27:09 by recherra          #+#    #+#             */
/*   Updated: 2025/03/24 16:02:00 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	re_calculate_factors(t_all_data *data)
{
	float	dx;
	float	dy;

	dx = data->endpoint.x - data->player.x;
	dy = data->endpoint.y - data->player.y;
	if (fabs(dx) >= fabs(dy))
		data->player.steps = fabs(dx);
	else
		data->player.steps = fabs(dy);
	data->player.factor_x = dx / data->player.steps;
	data->player.factor_y = dy / data->player.steps;
}
