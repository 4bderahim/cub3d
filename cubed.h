#ifndef CUBED_H
#define CUBED_H

#include </usr/local/include/mlx.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "libft/libft.h"

//game res
# define WIDTH 1200
# define HEIGHT 1200

typedef struct cu
{
    char **news;
    int fr;
    int fg;
    int fb;
    int cr;
    int cg;
    int cb;
    char **map;
    int map_height;
    int map_width;
    int tile;
} t_cu;

typedef struct s_mlx
{
    void	*connection;
    void	*window;
}			t_mlx;

typedef struct s_data
{
    void	*img;
    char	*addr;
    int		bits_per_pixel;
    int		line_length;
    int		endian;
}			t_data;

typedef struct s_minimap
{
    int tile;
    int width;
    int height;
} t_minimap;

typedef struct s_all_data
{
    t_mlx mlx;
    t_data minimap_img;
    t_data game_img;
    t_minimap minimap;
} t_all_data;

t_cu        *fetch__(void);


#endif