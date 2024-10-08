#include "cubed.h"

void	custom_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char	*dst;

    dst = data->addr + ((y * data->line_length) + (x * (data->bits_per_pixel / 8)));
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
    int j = 0;
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
    cu->map_width = pr_max;
    cu->map_height = i;
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
void initial_minimap(t_mlx mlx, t_data *imgs, t_minimap minim)
{
    imgs->img = mlx_new_image(mlx.connection, minim.width, minim.height);
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



void	mlx_initial(t_mlx *mlx, t_data *minimap, t_data *game_img, t_minimap minim)
{
    mlx->connection = mlx_init();
    init_error(mlx->connection);
    mlx->window = mlx_new_window(mlx->connection, WIDTH, HEIGHT, "trwadi");
    init_error(mlx->window);
    initial_minimap(*mlx, minimap, minim);
    initial_game(*mlx, game_img);
}

void    print_square(t_data *minimap_img, int tile_x, int tile_y, t_minimap minimap)
{
    int tile = minimap.tile;

    int i = 0;
    while (i < tile - 1)
    {
        int j = 0;
        while (j < tile - 1)
        {
            custom_mlx_pixel_put(minimap_img, tile_x + i, tile_y + j, 0xffffff);
            j++;
        }
        i++;
    }
}

void    mini_map(t_all_data *data, t_cu *cu_map)
{
    int i = 0;

    while (cu_map->map[i])
    {
        int j = 0;
        while (cu_map->map[i][j])
        {
            int tile_x = j * data->minimap.tile;
            int tile_y = i * data->minimap.tile;
            if (cu_map->map[i][j] == '1')
                print_square(&data->minimap_img, tile_x, tile_y, data->minimap);
            j++;
        }
        i++;
    }
}

int	key_check(int key)
{
    if (key == 0 || key == 1 || key == 2 || key == 13
        || key == 123 || key == 124)
    {
        return (1);
    }
    return (0);
}

void reset_game_image(t_all_data *data)
{
    (void)data;
}

void reset_minimap_image(t_all_data *data)
{
    data->minimap_img.img = mlx_new_image(data->mlx.connection, data->minimap.width, data->minimap.height);
    init_error(data->minimap_img.img);
    data->minimap_img.addr = mlx_get_data_addr(data->minimap_img.img, &data->minimap_img.bits_per_pixel,
                                                &data->minimap_img.line_length, &data->minimap_img.endian);
}

void	rebuild(t_all_data *data)
{
    mlx_destroy_image(data->mlx.connection, data->minimap_img.img);
    reset_minimap_image(data);
//    reset_game_image(data);
}

void put_images_to_window(t_all_data *data)
{
    mlx_put_image_to_window(data->mlx.connection, data->mlx.window, data->game_img.img, 0, 0);
    mlx_put_image_to_window(data->mlx.connection, data->mlx.window, data->minimap_img.img, 0, 0);
}

int	key_hook(int keycode, t_all_data *data)
{
    if (key_check(keycode))
        rebuild(data);
    if (keycode == 53)
    {
        mlx_destroy_window(data->mlx.connection, data->mlx.window);
        exit(0);
    }
    mini_map(data, data->cu_map);
    put_images_to_window(data);
    return (0);
}


void    game(t_data *game_img)
{
    for (int i = 0; i < WIDTH; i++)
        for (int j = 0; j < HEIGHT; j++)
            custom_mlx_pixel_put(game_img, i, j, 0x5135);
}


void minimap_calcs(t_all_data *data, t_cu *cu_map)
{
    data->minimap.tile = 32;
    data->minimap.width = cu_map->map_width * data->minimap.tile;
    data->minimap.height = cu_map->map_height * data->minimap.tile;
}

int main()
{
    t_all_data data;

    data.cu_map = fetch__();
    if (!data.cu_map)
        return (0);
    height_width(data.cu_map);
    minimap_calcs(&data, data.cu_map);
    mlx_initial(&data.mlx, &data.minimap_img, &data.game_img, data.minimap);
    mini_map(&data, data.cu_map);
    game(&data.game_img);
    put_images_to_window(&data);
    mlx_hook(data.mlx.window, 17, 0, close_btn, &data.mlx);
    mlx_hook(data.mlx.window, 2, 0, key_hook, &data);
    mlx_loop(data.mlx.connection);
}