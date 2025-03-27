/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:09:26 by recherra          #+#    #+#             */
/*   Updated: 2025/03/26 18:27:51 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	check_wall(t_all_data *data, int x, int y)
{
	if (data->cu_map->map[(int)(y / data->minimap.tile)][(int)(x
			/ data->minimap.tile)] == '1')
		return (1);
	else if (data->cu_map->map[(int)(y / data->minimap.tile)][(int)(x
			/ data->minimap.tile)] == '0')
		return (0);
	return (-1);
}

double	angle_fix(double angle)
{
	angle = fmod(angle, M_PI * 2);
	if (angle < 0)
		angle = (M_PI * 2) + angle;
	return (angle);
}

double	calculate__(double px, double py, double px_hit, double py_hit)
{
	return (sqrt(pow(px_hit - px, 2) + pow(py_hit - py, 2)));
}

void	set_direction(t_direction *direction, double ray_angle)
{
	direction->up = 0;
	if (ray_angle > 0 && ray_angle < M_PI)
		direction->up = 1;
	direction->down = !(direction->up);
	direction->left = 0;
	if (ray_angle < (M_PI / 2) || ray_angle > (M_PI + (M_PI / 2)))
		direction->left = 1;
	direction->right = !direction->left;
}
