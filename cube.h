/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:36:22 by recherra          #+#    #+#             */
/*   Updated: 2025/03/28 15:51:24 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdlib.h>

# define TILE 16
# define WIDTH 1920
# define HEIGHT 1080
# define ESC 53
# define RA 124
# define LA 123
# define WK 13
# define AK 0
# define SK 1
# define DK 2
# define TO_RAD 0.017453
# define N_RAYS WIDTH
# define MOVE_FACTOR 3

typedef struct cu
{
	char			**news;
	int				fr;
	int				fg;
	int				fb;
	int				cr;
	int				cg;
	int				cb;
	char			**map;
	int				map_height;
	int				map_width;
	int				tile;
}					t_cu;

typedef struct s_mlx
{
	void			*connection;
	void			*window;
}					t_mlx;

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;

typedef struct s_minimap
{
	int				tile;
	int				width;
	int				height;
}					t_minimap;

typedef struct s_player
{
	float			x;
	float			y;
	float			player_angle_rad;
	int				player_angle_degree;
	int				direction;
	float			fov_angle;
}					t_player;

typedef struct s_parsed_data
{
	int				f;
	int				c;
	int				i;
	char			nb[5];
}					t_parsed_data;

typedef struct s_direction
{
	int				up;
	int				down;
	int				right;
	int				left;
}					t_direction;

typedef struct s_ray
{
	float			ray_angle;
	float			wall_x;
	float			wall_y;
	float			distance;
	int				verical_hit;
	t_direction		direction;
}					t_ray;

typedef struct s_textures
{
	char			*path;
	void			*img;
	int				width;
	int				height;
	t_data			data;
}					t_textures;

typedef struct s_keys_state
{
	int				w;
	int				a;
	int				s;
	int				d;
	int				left_arrow;
	int				right_arrow;

}					t_keys_state;

typedef struct s_all_data
{
	t_mlx			mlx;
	t_data			minimap_img;
	t_data			game_img;
	t_minimap		minimap;
	t_cu			*cu_map;
	t_player		player;
	t_ray			*rays;
	t_textures		**news;
	t_keys_state	state;
	float			prev_x;
}					t_all_data;

typedef struct s_triangle
{
	float			adjacent;
	float			opposite;
	float			hypo;
}					t_triangle;

typedef struct s_rays_utils
{
	float			x_hit;
	float			y_hit;
	float			x_step;
	float			y_step;
	float			distance;
	t_triangle		triangle;
}					t_rays_utils;

typedef struct s_wall_data
{
	float			offset_x;
	float			offset_y;
	int				texture_num;
	int				texture_width;
	int				texture_height;
	int				distance_from_top;
	int				x;
	int				y;
	unsigned int	color;
}					t_wall_data;

// parsing
char				**free_str_null(char *str, t_cu *cu, char **map);
char				**alloc_map(char *str);
int					get_i_index(char **map, char *str);
int					not_valid(int i, int j, int map_len, char **map);
int					set_fr_fg_fb(t_cu *cu, char *s, int x);
int					parse_fc(t_parsed_data *data_set, char *str, t_cu *cu);
int					parse_news(t_parsed_data *data_set, char **news, char *str);
void				free_news(t_parsed_data *data_set, char **n);
int					map_beg(char *s, int i);
size_t				count_len(char *s);
char				*fill_(char *s, int index, int max);
int					check_map(char **map);
void				check_not_walled_map(t_cu *cu);
char				**get_map(int fd, t_cu *cu);
int					check_map__cf_news(t_parsed_data *data_set, char **news,
						char *str, t_cu *cu);
char				**set_parsed_data(t_parsed_data *data_set,
						int *map_check_ret);
int					set_fc__(t_parsed_data *data_set, char *str, t_cu *cu,
						char c);
void				free___(t_cu *map, int st);
char				*next_line(int fd, int len);
t_cu				*fetch__(void);
void				height_width(t_cu *cu);

//	load textures
void				init_textures(t_all_data *data);

// mlx setup
void				mlx_initial(t_mlx *mlx, t_data *game_img);
void				initial_minimap(t_mlx mlx, t_data *imgs, t_minimap minim);
void				initial_game(t_mlx mlx, t_data *imgs);
void				init_error(void *ptr);

// mlx rebuild
void				rebuild(t_all_data *data);
void				put_images_to_window(t_all_data *data);

// initial infos
void				initial_angle(t_all_data *data);
void				player_position(t_all_data *data, t_cu *cu_map);
void				minimap_calcs(t_all_data *data, t_cu *cu_map);

// hooks actions
// rotate
void				rotate(t_all_data *data, int direction);

// move
void				up_down(t_all_data *data, int direction);
void				right_left(t_all_data *data, int direction);

// print objects
void				print_player(t_data *minimap_img, int tile_x, int tile_y);

// custom pixel put
void				custom_mlx_pixel_put(t_data *data, int x, int y, int color);

// game rendering
void				game(t_all_data *data);
void				print_wall(t_all_data *data, float wall_height,
						int starting_x, int starting_y);
void				celine_and_floor(t_all_data *data);

// raycasting
void				init_rays(t_all_data *data);
void				cast_rays(t_all_data *data);
void				horizontal_intersection(t_all_data *data,
						t_direction direction, t_rays_utils *horizontal,
						float ray_angle);
void				vertical_intersection(t_all_data *data,
						t_direction direction, t_rays_utils *vertical,
						float ray_angle);

// ray casting utils
float				angle_fix(float angle);
float				calculate__(float px, float py, float px_hit, float py_hit);
void				set_direction(t_direction *direction, float ray_angle);
int					check_wall(t_all_data *data, int x, int y);
int					get_player_direction(char c);

// keys hook
int					key_press(int keycode, t_all_data *data);
int					key_release(int keycode, t_all_data *data);
void				set_state(t_all_data *data, int keycode, int state);
int					ultimate_hook(t_all_data *data);

// hooks utils utils
void				initialize_keys_state(t_all_data *data);
int					check_state(t_all_data *data);
void				re_render(t_all_data *data);

// collision
int					check_collision(t_all_data *data, float x, float y);

#endif
