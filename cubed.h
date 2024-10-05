#ifndef CUBED_H
#define CUBED_H

#include </usr/local/include/mlx.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "libft/libft.h"
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
    char ** map;
    int map_height;
    int map_width;
} t_cu;


t_cu        *fetch__(void);


#endif