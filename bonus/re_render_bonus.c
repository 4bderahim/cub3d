/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_render_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:10:27 by recherra          #+#    #+#             */
/*   Updated: 2025/03/28 17:20:36 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

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
