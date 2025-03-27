/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:31:45 by recherra          #+#    #+#             */
/*   Updated: 2025/03/27 22:35:56 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static int	check(t_all_data *data, float x, float y)
{
	if (data->cu_map->map[(int)(y / data->minimap.tile)][(int)(x
			/ data->minimap.tile)] == '1')
	{
		return (1);
	}
	return (0);
}

int	check_collision(t_all_data *data, float x, float y)
{
	int	i;

	i = -4;
	while (i <= 4)
	{
		if (x >= 0 && x < data->minimap.width && y >= 0
			&& y < data->minimap.height)
		{
			if (check(data, x, y + i))
				return (1);
		}
		i++;
	}
	i = -4;
	while (i <= 4)
	{
		if (x >= 0 && x < data->minimap.width && y >= 0
			&& y < data->minimap.height)
		{
			if (check(data, x + i, y))
				return (1);
		}
		i++;
	}
	return (0);
}
