/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:59:11 by recherra          #+#    #+#             */
/*   Updated: 2025/03/25 17:38:19 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	mlx_initial(t_mlx *mlx, t_data *game_img)
{
	mlx->connection = mlx_init();
	init_error(mlx->connection);
	mlx->window = mlx_new_window(mlx->connection, WIDTH, HEIGHT, "trwadi");
	init_error(mlx->window);
	initial_game(*mlx, game_img);
}

void	initial_game(t_mlx mlx, t_data *imgs)
{
	imgs->img = mlx_new_image(mlx.connection, WIDTH, HEIGHT);
	init_error(imgs->img);
	imgs->addr = mlx_get_data_addr(imgs->img, &imgs->bits_per_pixel,
			&imgs->line_length, &imgs->endian);
}
