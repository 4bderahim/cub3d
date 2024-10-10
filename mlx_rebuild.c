/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:13:36 by recherra          #+#    #+#             */
/*   Updated: 2024/10/10 21:13:37 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void reset_game_image(t_all_data *data)
{
    (void)data;
}

static void reset_minimap_image(t_all_data *data)
{
    data->minimap_img.img = mlx_new_image(data->mlx.connection, data->minimap.width, data->minimap.height);
    init_error(data->minimap_img.img);
    data->minimap_img.addr = mlx_get_data_addr(data->minimap_img.img, &data->minimap_img.bits_per_pixel,
                                               &data->minimap_img.line_length, &data->minimap_img.endian);
}

void	rebuild(t_all_data *data)
{
    mlx_destroy_image(data->mlx.connection, data->minimap_img.img);
    reset_minimap_image(data);
    reset_game_image(data);
}

void put_images_to_window(t_all_data *data)
{
    mlx_put_image_to_window(data->mlx.connection, data->mlx.window, data->game_img.img, 0, 0);
    mlx_put_image_to_window(data->mlx.connection, data->mlx.window, data->minimap_img.img, 0, 0);
}