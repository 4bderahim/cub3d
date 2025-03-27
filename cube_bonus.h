#ifndef CUBE_BONUS_H
#define CUBE_BONUS_H

// #include "/Users/ael-krid/minilibx_opengl_20191021/mlx.h"
// #include "/Users/ael-krid/MLX42/include/MLX42/MLX42.h"
#include "cube.h"

typedef struct s_coords
{
	double	x;
	double	y;
}			t_coords;

typedef struct s_dda_data
{
    double dx;
    double dy;
    double steps;

    double factor_x;
    double factor_y;

    double increment_x;
    double increment_y;
} t_dda_data;

typedef struct s_minimap_utils 
{	
	int		i;
	int		j;
	double	starting_x;
	double	starting_y;
	int		padding;
} t_minimap_utils;

int     mouse_hook(int x, int y, t_all_data *data);
void    mini_map(t_all_data *data);
void	dda(t_all_data *data, int padding);


#endif