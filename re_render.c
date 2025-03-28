/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:11:36 by recherra          #+#    #+#             */
/*   Updated: 2025/03/28 17:12:16 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	re_render(t_all_data *data)
{
	rebuild(data);
	free(data->rays);
	data->rays = NULL;
	init_rays(data);
	cast_rays(data);
	game(data);
	put_images_to_window(data);
}
