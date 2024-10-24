#ifndef CUBED_H
#define CUBED_H

#include <mlx.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "libft/libft.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define to_rad M_PI / 180
#define to_deg 180 / M_PI

#define WIDTH 1280
#define HEIGHT 720
#define N_RAYS WIDTH
#define thickness WIDTH / N_RAYS

#define MODE 0

#if MODE == 1
#define ESC 53
#define RA 124
#define LA 123
#define WK 13
#define AK 0
#define SK 1
#define DK 2

#else
#define ESC XK_Escape
#define RA XK_Right
#define LA XK_Left
#define WK XK_z
#define AK XK_q
#define SK XK_s
#define DK XK_d
#endif

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
    void *connection;
    void *window;
} t_mlx;

typedef struct s_data
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_data;

typedef struct s_minimap
{
    int tile;
    int width;
    int height;
} t_minimap;

typedef struct s_player
{
    float x;
    float y;
    float factor_x;
    float factor_y;
    float steps;
    float player_angle_rad;
    int player_angle_degree;
    int direction;
    float fov_angle;
} t_player;

typedef struct s_endpoint
{
    float x;
    float y;
} t_endpoint;

typedef struct s_raya
{
    float ray_angle;
    float wall_x;
    float wall_y;
    float distance;
    int verical_hit;
    int ray_up;
    int ray_down;
    int ray_left;
    int ray_right;
} t_ray;

typedef struct s_all_data
{
    t_mlx mlx;
    t_data minimap_img;
    t_data game_img;
    t_minimap minimap;
    t_cu *cu_map;
    t_player player;
    t_endpoint endpoint;
    t_ray *rays;
} t_all_data;

typedef struct s_direction
{
    int up;
    int down;
    int right;
    int left;
} t_direction;

typedef struct s_rays_utils
{
    float x_hit;
    float y_hit;
    float x_step;
    float y_step;
    float distance;
} t_rays_utils;

t_cu *fetch__(void);
void height_width(t_cu *cu);

// mlx setup
void mlx_initial(t_mlx *mlx, t_data *minimap, t_data *game_img, t_minimap minim);
void initial_minimap(t_mlx mlx, t_data *imgs, t_minimap minim);
void initial_game(t_mlx mlx, t_data *imgs);
void init_error(void *ptr);

// mlx rebuild
void rebuild(t_all_data *data);
void put_images_to_window(t_all_data *data);

// hooks
void re_pov(int keycode, t_all_data *data);
void re_position_player(int keycode, t_all_data *data);

// initial position
void initial_endpoint(t_all_data *data);

// rotate pov
void rotate(t_all_data *data, int direction);

// re calclulate factors
void re_calculate_factors(t_all_data *data);

// minimap
void mini_map(t_all_data *data, t_cu *cu_map, bool first_time);

// minimap pov
void minimap_pov(t_all_data *data);

// print objects
void print_square(t_data *minimap_img, int tile_x, int tile_y, t_minimap minimap);
void print_player(t_data *minimap_img, int tile_x, int tile_y, t_minimap minimap);

// custom pixel put
void custom_mlx_pixel_put(t_data *data, int x, int y, int color);
void set_direction(t_direction *direction, float ray_angle);

#endif