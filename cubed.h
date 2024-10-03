#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 

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
} t_cu;