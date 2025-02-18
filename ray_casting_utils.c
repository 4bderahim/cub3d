/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:09:26 by recherra          #+#    #+#             */
/*   Updated: 2025/02/18 16:31:21 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

float	angle_fix(float angle)
{
	angle = remainder(angle, M_PI * 2);
	if (angle < 0)
	{
		angle = (M_PI * 2) + angle;
	}
	return (angle);
}

float	calculate__(float px, float py, float px_hit, float py_hit)
{
	return (sqrt(pow(px_hit - px, 2) + pow(py_hit - py, 2)));
}

void	set_direction(t_direction *direction, float ray_angle)
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
