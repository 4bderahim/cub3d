#ifndef CUBED_H
#define CUBED_H

#include "/Users/ael-krid/minilibx_opengl_20191021/mlx.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "libft/libft.h"
#include "stdbool.h"

#define to_deg M_PI / 180

//game res
# define WIDTH 1200
# define HEIGHT 1200
# define N_RAYS 10

//keys
#define RA 124
#define LA 123
#define WK 13
#define AK 0
#define SK 1
#define DK 2

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

typedef struct s_player
{
    float x;
    float y;
    float factor_x;
    float factor_y;
    float steps;
    float player_angle_rad;
    int direction;
    float fov_angle;
} t_player;

typedef struct s_endpoint
{
    float x;
    float y;
} t_endpoint;

typedef struct s_ray
{
    float   ray_angle;
    float   wall_x;
    float   wall_y;
    float   distance;
    int     verical_hit;
    int     ray_up;
    int     ray_down;
    int     ray_left;
    int     ray_right;
}t_ray;

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


t_cu        *fetch__(void);
void height_width(t_cu *cu);

//mlx setup
void	mlx_initial(t_mlx *mlx, t_data *minimap, t_data *game_img, t_minimap minim);
void initial_minimap(t_mlx mlx, t_data *imgs, t_minimap minim);
void initial_game(t_mlx mlx, t_data *imgs);
void	init_error(void *ptr);

//mlx rebuild
void	rebuild(t_all_data *data);
void put_images_to_window(t_all_data *data);

//hooks
void    re_pov(int keycode, t_all_data *data);
void    re_position_player(int keycode, t_all_data *data);

//initial position
void    initial_endpoint(t_all_data *data);

//rotate pov
void rotate(t_all_data *data, int direction);

//re calclulate factors
void    re_calculate_factors(t_all_data *data);

//minimap
void    mini_map(t_all_data *data, t_cu *cu_map, bool first_time);

//minimap pov
void    minimap_pov(t_all_data *data);

//print objects
void    print_square(t_data *minimap_img, int tile_x, int tile_y, t_minimap minimap);
void    print_player(t_data *minimap_img, int tile_x, int tile_y, t_minimap minimap);

//custom pixel put
void	custom_mlx_pixel_put(t_data *data, int x, int y, int color);



#endif