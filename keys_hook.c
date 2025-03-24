/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:47:25 by recherra          #+#    #+#             */
/*   Updated: 2025/03/24 16:02:00 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	key_check(int key)
{
	if (key == WK || key == AK || key == SK || key == DK || key == RA
		|| key == LA)
		return (1);
	return (0);
}

int	key_press(int keycode, t_all_data *data)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(data->mlx.connection, data->mlx.window);
		exit(0);
	}
	if (key_check(keycode) == 0)
		return (0);
	set_state(data, keycode, 1);
	return (0);
}

int	key_release(int keycode, t_all_data *data)
{
	set_state(data, keycode, 0);
	return (0);
}

void	set_state(t_all_data *data, int keycode, int state)
{
	if (keycode == WK)
		data->state.w = state;
	if (keycode == SK)
		data->state.s = state;
	if (keycode == AK)
		data->state.a = state;
	if (keycode == DK)
		data->state.d = state;
	if (keycode == RA)
		data->state.right_arrow = state;
	if (keycode == LA)
		data->state.left_arrow = state;
}

int	ultimate_hook(t_all_data *data)
{
	int	check;

	check = 0;
	if (check_state(data))
		check = 1;
	if (data->state.w)
		up_down(data, -1);
	if (data->state.s)
		up_down(data, 1);
	if (data->state.a)
		right_left(data, -1);
	if (data->state.d)
		right_left(data, 1);
	if (data->state.right_arrow)
		rotate(data, 1, false);
	if (data->state.left_arrow)
		rotate(data, -1, false);
	if (check == 1)
		re_render(data);
	return (0);
}
