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

void	mlx_initial(t_mlx *mlx, t_data *img)
{
    mlx->connection = mlx_init();
    init_error(mlx->connection);
    mlx->window = mlx_new_window(mlx->connection, WIDTH, HEIGHT, "trwadi");
    init_error(mlx->window);
    img->img = mlx_new_image(mlx->connection, WIDTH, HEIGHT);
    init_error(img->img);
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
                                  &img->line_length, &img->endian);
}

int main()
{
    t_cu *cu_map;
    t_mlx mlx;
    t_data		img;

    cu_map = fetch__();
    if (!cu_map)
        return (0);
    height_width(cu_map);
    mlx_initial(&mlx, &img);
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
            custom_mlx_pixel_put(&img, i, j, 0x455445);
    }
    mlx_put_image_to_window(mlx.connection, mlx.window, img.img, 0, 0);
    mlx_key_hook(mlx.window, events_manager, &mlx);
    mlx_hook(mlx.window, 17, 0, close_btn, &mlx);
    mlx_loop(mlx.connection);
}