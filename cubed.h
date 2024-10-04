#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include "./MLX42.h"
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