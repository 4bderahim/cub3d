#ifndef CUBED_H
# define CUBED_H


// #include "/Users/ael-krid/minilibx_opengl_20191021/mlx.h"
// #include "/Users/ael-krid/MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>

# define to_rad M_PI / 180
# define to_deg 180 / M_PI
# define N_RAYS WIDTH

# define MODE 1
# if MODE == 1
#  define TILE 16
#  define WIDTH 1920
#  define HEIGHT 1080
#  define MINIMAP_WIDTH 426
#  define MINIMAP_HEIGHT 240
#  define ESC 53
#  define RA 124
#  define LA 123
#  define WK 13
#  define AK 0
#  define SK 1
#  define DK 2

# else

#  define M_PI 3.14159265358979323846
#  define TILE 16
#  define WIDTH 1280
#  define HEIGHT 720
#  include <X11/Xlib.h>
#  include <X11/keysym.h>
#  define ESC XK_Escape
#  define RA XK_Right
#  define LA XK_Left
#  define WK XK_z
#  define AK XK_q
#  define SK XK_s
#  define DK XK_d

# endif

typedef struct s_rotation
{
	float	cos_theta;
	float	sin_theta;
	float	radian;
	float	delta_x;
	float	delta_y;
	int		degree_to_add;
	float	x;
	float	y;
} t_rotation;

typedef struct cu
{
	char		**news;
	int			fr;
	int			fg;
	int			fb;
	int			cr;
	int			cg;
	int			cb;
	char		**map;
	int			map_height;
	int			map_width;
	int			tile;
}				t_cu;

typedef struct s_mlx
{
	void		*connection;
	void		*window;
}				t_mlx;

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct s_minimap
{
	int			tile;
	int			width;
	int			height;
}				t_minimap;

typedef struct s_player
{
	float		x;
	float		y;
	float		factor_x;
	float		factor_y;
	float		steps;
	float		player_angle_rad;
	int			player_angle_degree;
	int			direction;
	float		fov_angle;
}				t_player;
typedef struct s_parsed_data
{
	int			f;
	int			c;
	int			i;
	char		nb[5];
}				t_parsed_data;

typedef struct s_endpoint
{
	float		x;
	float		y;
}				t_endpoint;

typedef struct s_raya
{
	float		ray_angle;
	float		wall_x;
	float		wall_y;
	float		distance;
	int			verical_hit;
	int			ray_up;
	int			ray_down;
	int			ray_left;
	int			ray_right;
}				t_ray;

typedef struct s_textures
{
	char		*path;
	void		*img;
	int			width;
	int			height;
	t_data		data;
}				t_textures;

typedef struct s_all_data
{
	t_mlx		mlx;
	t_data		minimap_img;
	t_data		game_img;
	t_minimap	minimap;
	t_cu		*cu_map;
	t_player	player;
	t_endpoint	endpoint;
	t_ray		*rays;
	t_textures	**news;
	float		testing_factor;
}				t_all_data;

typedef struct s_direction
{
	int			up;
	int			down;
	int			right;
	int			left;
}				t_direction;

typedef struct s_rays_utils
{
	float		x_hit;
	float		y_hit;
	float		x_step;
	float		y_step;
	float		distance;
}				t_rays_utils;


typedef struct s_dda_data
{
	float	dx;
	float	dy;
	float	steps;
	
	
	float	factor_x;
	float	factor_y;

	
	float	increment_x;
	float	increment_y;
} t_dda_data;


typedef struct s_wall_data
{
	double			offset_x;
	double			offset_y;
	int				texture_num;
	int				texture_width;
	int				texture_height;
	int				distance_from_top;
	int				x;
	int				y;
	unsigned int	color;
} t_wall_data;


int				map_beg(char *s, int i);
size_t			count_len(char *s);
char			*fill_(char *s, int index);
int				check_map(char **map);
void			check_not_walled_map(t_cu *cu);
char			**get_map(int fd);
int				check_map__cf_news(t_parsed_data *data_set, char **news,
					char *str, t_cu *cu);
char			**set_parsed_data(t_parsed_data *data_set, int *map_check_ret);
int				set_fc__(t_parsed_data *data_set, char *str, t_cu *cu, char c);
void			free___(t_cu *map, int st);
char			*next_line(int fd, int len);
t_cu			*fetch__(void);
void			height_width(t_cu *cu);
void	        init_textures(t_all_data *data);



// mlx setup
void			mlx_initial(t_mlx *mlx, t_data *minimap, t_data *game_img,
					t_minimap minim);
void			initial_minimap(t_mlx mlx, t_data *imgs, t_minimap minim);
void			initial_game(t_mlx mlx, t_data *imgs);
void			init_error(void *ptr);

// mlx rebuild
void			rebuild(t_all_data *data);
void			put_images_to_window(t_all_data *data);

// hooks
void			re_pov(int keycode, t_all_data *data);
void			re_position_player(int keycode, t_all_data *data);

// initial position
void			initial_endpoint(t_all_data *data);

// rotate pov
void			rotate(t_all_data *data, int direction);

// re calclulate factors
void			re_calculate_factors(t_all_data *data);

// minimap
void			mini_map(t_all_data *data, t_cu *cu_map, bool first_time);

// minimap pov
void			minimap_pov(t_all_data *data);

// print objects
void			print_square(t_data *minimap_img, int tile_x, int tile_y,
					t_minimap minimap);
void			print_player(t_data *minimap_img, int tile_x, int tile_y,
					t_minimap minimap);
                    
// custom pixel put
void			custom_mlx_pixel_put(t_data *data, int x, int y, int color);
void			set_direction(t_direction *direction, float ray_angle);

//hooks utils
void 			up_down(t_all_data *data, int direction);
void 			right_left(t_all_data *data, int direction);

//dda
void	ray_dda(t_all_data *data, float ray_x, float ray_y);

//render wall
void	print_wall(t_all_data *data, float wall_height, int starting_x,
		int starting_y);

//celine and floor
void	celine_and_floor(t_all_data *data);

void	game(t_all_data *data);


void	render__rays(t_all_data *data);
void	init_rays(t_all_data *data);

void	 minimap_calcs(t_all_data *data, t_cu *cu_map);

void	cast_rays(t_all_data *data);
void	horizontal_intersection(t_all_data *data, t_direction direction,
		t_rays_utils *horizontal, float ray_angle);
void	vertical_intersection(t_all_data *data, t_direction direction,
		t_rays_utils *vertical, float ray_angle);

// ray casting utils
float	angle_fix(float angle);
float	calculate__(float px, float py, float px_hit, float py_hit);
void	set_direction(t_direction *direction, float ray_angle);


#endif