#ifndef CUBE_H
#define CUBE_H

// #include "/Users/ael-krid/minilibx_opengl_20191021/mlx.h"
// #include "/Users/ael-krid/MLX42/include/MLX42/MLX42.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <math.h>
#include <mlx.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODE 1

#if MODE == 1

#define TILE 16
#define WIDTH 1920
#define HEIGHT 1080
#define ESC 53
#define RA 124
#define LA 123
#define WK 13
#define AK 0
#define SK 1
#define DK 2

#else

#define M_PI 3.14159265358979323846
#define TILE 16
#define WIDTH 1280
#define HEIGHT 720
#include <X11/Xlib.h>
#include <X11/keysym.h>
#define ESC XK_Escape
#define RA XK_Right
#define LA XK_Left
#define WK XK_z
#define AK XK_q
#define SK XK_s
#define DK XK_d

#endif


#define to_rad M_PI / 180
#define to_deg 180 / M_PI
#define N_RAYS WIDTH

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
    double x;
    double y;
    double factor_x;
    double factor_y;
    double steps;
    double player_angle_rad;
    int player_angle_degree;
    int direction;
    double fov_angle;
} t_player;

typedef struct s_parsed_data
{
    int f;
    int c;
    int i;
    char nb[5];
} t_parsed_data;

typedef struct s_direction
{
    int up;
    int down;
    int right;
    int left;
} t_direction;

typedef struct s_ray
{
    double ray_angle;
    double wall_x;
    double wall_y;
    double distance;
    int verical_hit;
    t_direction direction;
} t_ray;

typedef struct s_textures
{
    char *path;
    void *img;
    int width;
    int height;
    t_data data;
} t_textures;

typedef struct s_keys_state
{
    int w;
    int a;
    int s;
    int d;
    int left_arrow;
    int right_arrow;

} t_keys_state;

typedef struct s_all_data
{
    t_mlx mlx;
    t_data minimap_img;
    t_data game_img;
    t_minimap minimap;
    t_cu *cu_map;
    t_player player;
    t_ray *rays;
    t_textures **news;
    t_keys_state state;
    double prev_x;
} t_all_data;

typedef struct s_triangle
{
    double adjacent;
    double opposite;
    double hypo;
} t_triangle;

typedef struct s_rays_utils
{
    double x_hit;
    double y_hit;
    double x_step;
    double y_step;
    double distance;
    t_triangle triangle;
} t_rays_utils;


typedef struct s_wall_data
{
    double offset_x;
    double offset_y;
    int texture_num;
    int texture_width;
    int texture_height;
    int distance_from_top;
    int x;
    int y;
    unsigned int color;
} t_wall_data;


int not_valid(int i, int j, int map_len , char **map);
int set_fr_fg_fb(t_cu *cu, char *s, int x);
int parse_fc(t_parsed_data *data_set, char *str, t_cu *cu);
int parse_news(t_parsed_data *data_set, char **news, char *str);
void free_news(t_parsed_data *data_set, char **n);

int map_beg(char *s, int i);
size_t count_len(char *s);
char *fill_(char *s, int index, int max);
int check_map(char **map);
void check_not_walled_map(t_cu *cu);
char **get_map(int fd, t_cu *cu);
int check_map__cf_news(t_parsed_data *data_set, char **news,
                       char *str, t_cu *cu);
char **set_parsed_data(t_parsed_data *data_set, int *map_check_ret);
int set_fc__(t_parsed_data *data_set, char *str, t_cu *cu, char c);
void free___(t_cu *map, int st);
char *next_line(int fd, int len);
t_cu *fetch__(void);
void height_width(t_cu *cu);
void init_textures(t_all_data *data);

// mlx setup
void mlx_initial(t_mlx *mlx, t_data *game_img);
void initial_minimap(t_mlx mlx, t_data *imgs, t_minimap minim);
void initial_game(t_mlx mlx, t_data *imgs);
void init_error(void *ptr);

// mlx rebuild
void rebuild(t_all_data *data);
void put_images_to_window(t_all_data *data);

// initial position
void initial_angle(t_all_data *data);
void player_position(t_all_data *data, t_cu *cu_map);

// rotate pov
void rotate(t_all_data *data, int direction, bool from_mouse);

// re calclulate factors
void re_calculate_factors(t_all_data *data);


// minimap pov
void minimap_pov(t_all_data *data);

// print objects
void print_player(t_data *minimap_img, int tile_x, int tile_y);

// custom pixel put
void custom_mlx_pixel_put(t_data *data, int x, int y, int color);
void set_direction(t_direction *direction, double ray_angle);

// hooks utils
void up_down(t_all_data *data, int direction);
void right_left(t_all_data *data, int direction);

// render wall
void print_wall(t_all_data *data, double wall_height, int starting_x,
                int starting_y);

// celine and floor
void celine_and_floor(t_all_data *data);

void game(t_all_data *data);

void render__rays(t_all_data *data);
void init_rays(t_all_data *data);

void minimap_calcs(t_all_data *data, t_cu *cu_map);

void cast_rays(t_all_data *data);
void horizontal_intersection(t_all_data *data, t_direction direction,
                             t_rays_utils *horizontal, double ray_angle);
void vertical_intersection(t_all_data *data, t_direction direction,
                           t_rays_utils *vertical, double ray_angle);

// ray casting utils
double angle_fix(double angle);
double calculate__(double px, double py, double px_hit, double py_hit);
void set_direction(t_direction *direction, double ray_angle);

int check_wall(t_all_data *data, int x, int y);

int get_player_direction(char c);


// keys hook 
int     key_press(int keycode, t_all_data *data);
int     key_release(int keycode, t_all_data *data);
void    set_state(t_all_data *data, int keycode, int state);
int     ultimate_hook(t_all_data *data);


// hooks utils utils
void    re_render(t_all_data *data);
int check_state(t_all_data *data);
void initialize_keys_state(t_all_data *data);

#endif