/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 21:06:58 by recherra          #+#    #+#             */
/*   Updated: 2025/03/24 16:02:00 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	custom_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + ((y * data->line_length) + (x * (data->bits_per_pixel
					/ 8)));
	*(unsigned int *)dst = color;
}
