/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:12:50 by recherra          #+#    #+#             */
/*   Updated: 2025/03/19 16:18:05 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	close_btn(t_all_data *data)
{
	mlx_destroy_image(data->mlx.connection, data->game_img.img);
	mlx_destroy_window(data->mlx.connection, data->mlx.window);
	exit(0);
}

int	key_check(int key)
{
	if (key == WK || key == AK || key == SK || key == DK || key == RA
		|| key == LA || key == ESC)
		return (1);
	return (0);
}

int	key_hook(int keycode, t_all_data *data)
{
	if (key_check(keycode))
		rebuild(data);
	if (keycode == ESC)
	{
		mlx_destroy_window(data->mlx.connection, data->mlx.window);
		exit(0);
	}
	re_pov(keycode, data);
	re_position_player(keycode, data);
	free(data->rays);
	data->rays = NULL;
	init_rays(data);
	cast_rays(data);
	game(data);
	mini_map(data, data->cu_map);
	put_images_to_window(data);
	return (0);
}

int	main(void)
{
	t_all_data	data;

	data.cu_map = fetch__();
	if (!data.cu_map)
		return (0);
	height_width(data.cu_map);
	minimap_calcs(&data, data.cu_map);

	mlx_initial(&data.mlx, &data.game_img);
	init_textures(&data);
	player_position(&data, data.cu_map);
	initial_endpoint(&data);
	init_rays(&data);
	cast_rays(&data);
	game(&data);
	mini_map(&data, data.cu_map);
	put_images_to_window(&data);
	mlx_hook(data.mlx.window, 17, 0, close_btn, &data);
	mlx_hook(data.mlx.window, 2, 1L << 0, key_hook, &data);
	mlx_loop(data.mlx.connection);
}
