/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:12:50 by recherra          #+#    #+#             */
/*   Updated: 2025/03/17 18:01:45 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	close_btn(t_all_data *data)
{
	mlx_destroy_image(data->mlx.connection, data->minimap_img.img);
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
	mini_map(data, data->cu_map);
	free(data->rays);
	data->rays = NULL;
	init_rays(data);
	cast_rays(data);
	render__rays(data);
	game(data);
	put_images_to_window(data);
	return (0);
}


void	print_map(t_cu *map)
{
	int i = 0;
	int j = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			printf("%c", map->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	main(void)
{
	t_all_data	data;

	data.cu_map = fetch__();
	if (!data.cu_map)
		return (0);
	height_width(data.cu_map);
	minimap_calcs(&data, data.cu_map);
	print_map(data.cu_map);
	// exit(1);

	mlx_initial(&data.mlx, &data.minimap_img, &data.game_img, data.minimap);
	init_textures(&data);
	player_position(&data, data.cu_map);
	mini_map(&data, data.cu_map);
	initial_endpoint(&data);
	init_rays(&data);
	cast_rays(&data);
	render__rays(&data);
	game(&data);
	put_images_to_window(&data);
	mlx_hook(data.mlx.window, 17, 0, close_btn, &data);
	mlx_hook(data.mlx.window, 2, 1L << 0, key_hook, &data);
	mlx_loop(data.mlx.connection);
}
