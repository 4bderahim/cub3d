/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:59:11 by recherra          #+#    #+#             */
/*   Updated: 2025/02/17 13:31:09 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	mlx_initial(t_mlx *mlx, t_data *minimap, t_data *game_img,
		t_minimap minim)
{
	mlx->connection = mlx_init();
	init_error(mlx->connection);
	mlx->window = mlx_new_window(mlx->connection, WIDTH, HEIGHT, "trwadi");
	init_error(mlx->window);
	initial_minimap(*mlx, minimap, minim);
	initial_game(*mlx, game_img);
}

// minimap image
void	initial_minimap(t_mlx mlx, t_data *imgs, t_minimap minim)
{
	imgs->img = mlx_new_image(mlx.connection, minim.width, minim.height);
	init_error(imgs->img);
	imgs->addr = mlx_get_data_addr(imgs->img, &imgs->bits_per_pixel,
			&imgs->line_length, &imgs->endian);
}

// game image
void	initial_game(t_mlx mlx, t_data *imgs)
{
	imgs->img = mlx_new_image(mlx.connection, WIDTH, HEIGHT);
	init_error(imgs->img);
	imgs->addr = mlx_get_data_addr(imgs->img, &imgs->bits_per_pixel,
			&imgs->line_length, &imgs->endian);
}
