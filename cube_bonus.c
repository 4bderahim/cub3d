/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:59:39 by recherra          #+#    #+#             */
/*   Updated: 2025/03/24 16:06:42 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

int	close_btn(t_all_data *data)
{
	mlx_destroy_image(data->mlx.connection, data->game_img.img);
	mlx_destroy_window(data->mlx.connection, data->mlx.window);
	exit(0);
}

int	main(void)
{
	t_all_data	data;

	data.cu_map = fetch__();
	if (!data.cu_map)
		return (0);
	initialize_keys_state(&data);
	height_width(data.cu_map);
	minimap_calcs(&data, data.cu_map);
	mlx_initial(&data.mlx, &data.game_img);
	init_textures(&data);
	player_position(&data, data.cu_map);
	initial_endpoint(&data);
	init_rays(&data);
	cast_rays(&data);
	game(&data);
	mini_map(&data);
	put_images_to_window(&data);
	mlx_hook(data.mlx.window, 2, 1L << 0, key_press, &data);
	mlx_hook(data.mlx.window, 3, 1L << 1, key_release, &data);
	mlx_hook(data.mlx.window, 6, 1L << 6, mouse_hook, &data);
	mlx_loop_hook(data.mlx.connection, ultimate_hook, &data);
	mlx_hook(data.mlx.window, 17, 0, close_btn, &data);
	mlx_loop(data.mlx.connection);
}
