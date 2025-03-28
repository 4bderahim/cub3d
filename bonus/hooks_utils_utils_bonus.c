/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:56:37 by recherra          #+#    #+#             */
/*   Updated: 2025/03/27 22:26:48 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

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

void	re_render(t_all_data *data)
{
	rebuild(data);
	free(data->rays);
	data->rays = NULL;
	init_rays(data);
	cast_rays(data);
	game(data);
	mini_map(data);
	put_images_to_window(data);
}
