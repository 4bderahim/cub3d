#include "cubed.h"

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

void	custom_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char	*dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int	close_btn(t_mlx *mlx)
{
    mlx_destroy_window(mlx->connection, mlx->window);
    exit(0);
}

void height_width(t_cu *cu)
{
    int i;
    int j;
    char **map;
    int pr_max;
    map = cu->map;
    i = 0;
    pr_max = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
            j++;
        if (j > pr_max)
            pr_max = j;
        i++;
    }
    cu->map_width = j-1;
    cu->map_height = i-1;
}


int	events_manager(int keycode, t_mlx *mlx)
{
    if (keycode == 53)
    {
        mlx_destroy_window(mlx->connection, mlx->window);
        exit(0);
    }
    return (0);
}

void ft_putstr(char *str)
{
    int i = 0;
    while (str[i])
        write(1, &str[i++], 1);
}

void	print_error(char *error_msg)
{
    ft_putstr(error_msg);
    exit(1);
}


void	init_error(void *ptr)
{
    if (!ptr)
    {
        print_error("Unknown error happened!");
        exit(1);
    }
}


//minimap image
void initial_minimap(t_mlx mlx, t_data *imgs)
{
    imgs->img = mlx_new_image(mlx.connection, WIDTH / 2, HEIGHT / 3);
    init_error(imgs->img);
    imgs->addr = mlx_get_data_addr(imgs->img, &imgs->bits_per_pixel, &imgs->line_length, &imgs->endian);
}

////game image
void initial_game(t_mlx mlx, t_data *imgs)
{
    imgs->img = mlx_new_image(mlx.connection, WIDTH, HEIGHT);
    init_error(imgs->img);
    imgs->addr = mlx_get_data_addr(imgs->img, &imgs->bits_per_pixel, &imgs->line_length, &imgs->endian);
}



void	mlx_initial(t_mlx *mlx, t_data *minimap, t_data *game_img)
{
    mlx->connection = mlx_init();
    init_error(mlx->connection);
    mlx->window = mlx_new_window(mlx->connection, WIDTH, HEIGHT, "trwadi");
    init_error(mlx->window);
    initial_minimap(*mlx, minimap);
    initial_game(*mlx, game_img);
}

int main()
{
    t_cu *cu_map;
    t_mlx mlx;
    t_data minimap_img;
    t_data game_img;

    cu_map = fetch__();
    if (!cu_map)
        return (0);
    height_width(cu_map);
    mlx_initial(&mlx, &minimap_img, &game_img);
    for (int i = 0; i < WIDTH / 2; i++)
    {
        for (int j = 0; j < HEIGHT / 3; j++)
            custom_mlx_pixel_put(&minimap_img, i, j, 0x455445);
    }
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
            custom_mlx_pixel_put(&game_img, i, j, 0x255);
    }
    mlx_put_image_to_window(mlx.connection, mlx.window, game_img.img, 0, 0);
    mlx_put_image_to_window(mlx.connection, mlx.window, minimap_img.img, 0, 0);
    mlx_key_hook(mlx.window, events_manager, &mlx);
    mlx_hook(mlx.window, 17, 0, close_btn, &mlx);
    mlx_loop(mlx.connection);
}