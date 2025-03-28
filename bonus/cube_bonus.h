/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:36:30 by recherra          #+#    #+#             */
/*   Updated: 2025/03/27 22:36:31 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_BONUS_H
# define CUBE_BONUS_H

# include "../cube.h"

typedef struct s_coords
{
	float	x;
	float	y;
}			t_coords;

typedef struct s_dda_data
{
	float	dx;
	float	dy;
	float	steps;

	float	factor_x;
	float	factor_y;

	float	increment_x;
	float	increment_y;
}			t_dda_data;

typedef struct s_minimap_utils
{
	int		i;
	int		j;
	float	starting_x;
	float	starting_y;
	int		padding;
}			t_minimap_utils;

int			mouse_hook(int x, int y, t_all_data *data);
void		mini_map(t_all_data *data);
void		dda(t_all_data *data, int padding);

#endif