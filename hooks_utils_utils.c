/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:56:37 by recherra          #+#    #+#             */
/*   Updated: 2025/03/28 17:16:09 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	close_btn(t_all_data *data)
{
	mlx_destroy_image(data->mlx.connection, data->game_img.img);
	mlx_destroy_window(data->mlx.connection, data->mlx.window);
	exit(0);
}

void	initialize_keys_state(t_all_data *data)
{
	data->state.w = 0;
	data->state.a = 0;
	data->state.s = 0;
	data->state.d = 0;
	data->state.left_arrow = 0;
	data->state.right_arrow = 0;
	data->prev_x = 0;
}

int	check_state(t_all_data *data)
{
	if (data->state.w || data->state.s || data->state.a || data->state.d
		|| data->state.right_arrow || data->state.left_arrow)
		return (1);
	return (0);
}
