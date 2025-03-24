/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:51:23 by recherra          #+#    #+#             */
/*   Updated: 2025/03/24 22:20:17 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

int	mouse_hook(int x, int y, t_all_data *data)
{
	(void)y;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		if (x < data->prev_x)
			rotate(data, -1, true);
		else if (x > data->prev_x)
			rotate(data, 1, true);
		data->prev_x = x;
		re_render(data);
	}
	return (0);
}
