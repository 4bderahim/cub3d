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


void    print_player(t_data *minimap_img, int tile_x, int tile_y, t_minimap minimap)
{
    int dot = minimap.tile / 6;

    int i = 0;
    while (i < dot)
    {
        int j = 0;
        while (j < dot)
        {
            custom_mlx_pixel_put(minimap_img, tile_x + i, tile_y + j, 0xFF0000);
            j++;
        }
        i++;
    }

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

int check_player(char c)
{
    if (c == 'N' || c == 'S' || c == 'E' ||  c==  'W')
        return c;
    return 0;
}

void    mini_map(t_all_data *data, t_cu *cu_map, bool first_time)
{
    int i = 0;
    int direction = 0;

    while (cu_map->map[i])
    {
        int j = 0;
        int tile_y = i * data->minimap.tile;
        while (cu_map->map[i][j])
        {
            direction = check_player(cu_map->map[i][j]);
            int tile_x = j * data->minimap.tile;
            if (cu_map->map[i][j] == '1')
                print_square(&data->minimap_img, tile_x, tile_y, data->minimap);
            if (direction)
            {
                data->player.direction = direction;
                if (first_time)
                {
                    data->player.x = tile_x;
                    data->player.y = tile_y;
                }
                if (data->player.x > 0 && data->player.x < data->minimap.width && data->player.y > 0 && data->player.y < data->minimap.height)
                {
                    print_player(&data->minimap_img, data->player.x, data->player.y, data->minimap);
                }
            }
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



void rotate(t_all_data *data, int direction)
{
    float	cos_theta;
    float	sin_theta;
    float	tmp;
    float	radian;

    radian = (10 * (M_PI / 180)) * direction;
    cos_theta = cos(radian);
    sin_theta = sin(radian);

    float x = ((data->endpoint.x - data->player.x) * cos_theta) - (sin_theta * (data->endpoint.y - data->player.y)) + data->player.x;
    float y = ((data->endpoint.x - data->player.x) * sin_theta) + (cos_theta * (data->endpoint.y - data->player.y)) + data->player.y;
    data->endpoint.x = x;
    data->endpoint.y = y;
}

void    re_pov(int keycode, t_all_data *data)
{
    if (keycode == RA)
        rotate(data, 1);
    else if (keycode == LA)
        rotate(data, -1);
}

void    re_calculate_factors(t_all_data *data)
{
    int i = 0;

    float dx = data->endpoint.x - data->player.x;
    float dy = data->endpoint.y - data->player.y;
    if (fabs(dx) >= fabs(dy))
        data->player.steps = fabs(dx);
    else
        data->player.steps = fabs(dy);
    data->player.factor_x = dx / data->player.steps;
    data->player.factor_y = dy / data->player.steps;
}


void re_position_player(int keycode, t_all_data *data)
{
    if (keycode == WK)
    {
        data->player.x += data->player.factor_x * 5;
        data->player.y += data->player.factor_y * 5;
        data->endpoint.x += data->player.factor_x * 5;
        data->endpoint.y += data->player.factor_y * 5;
    }
    else if (keycode == AK)
    {
        data->player.x += data->player.factor_x * 5;
        data->player.y += data->player.factor_y * 5;
        data->endpoint.x += data->player.factor_x * 5;
        data->endpoint.y += data->player.factor_y * 5;
        printf("\nPlayer x: %f\nPlayer y: %f\nfactor x: %f\nfactor y: %f\n", data->player.x, data->player.y, data->player.factor_x, data->player.factor_y);
    }
//    else if (keycode == SK)
//    {
//
//    }
//    else if (keycode == DK)
//    {
//
//    }
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
    //  recalculate endpoint pov line
    re_pov(keycode, data);
    //  recalculate increment factors
    re_calculate_factors(data);
    // re-position player
    re_position_player(keycode, data);
    //    redraw line
    mini_map(data, data->cu_map, false);
    minimap_pov(data);
    //redraw monimap
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
    data->minimap.tile = 25;
    data->minimap.width = cu_map->map_width * data->minimap.tile;
    data->minimap.height = cu_map->map_height * data->minimap.tile;
}

int north(int c)
{
    return c == 'N';
}

int south(int c)
{
    return c == 'S';
}

int east(int c)
{
    return c == 'E';
}

int west(int c)
{
    return c == 'W';
}


void    initial_endpoint(t_all_data *data)
{
    int direction = data->player.direction;
    int player_x = data->player.x;
    int player_y = data->player.y;

    if (north(direction) || south(direction))
    {
        if (north(direction))
        {
            data->endpoint.x = player_x;
            data->endpoint.y = 0;
            data->endpoint.initial_degree = 270;
        }
        else if (south(direction))
        {
            data->endpoint.x = player_x;
            data->endpoint.y = data->minimap.height;
            data->endpoint.initial_degree = 90;
        }
    }
    else if (east(direction) || west(direction))
    {
        if (east(direction))
        {
            data->endpoint.x = data->minimap.width;
            data->endpoint.y = player_y;
            data->endpoint.initial_degree = 0;
        }
        else if (west(direction))
        {
            data->endpoint.x = 0;
            data->endpoint.y = player_y;
            data->endpoint.initial_degree = 180;
        }
    }
}



void dda(t_all_data *data)
{
    int i = 0;
    float increment_x = data->player.x;
    float increment_y = data->player.y;

    while (i < 50)
    {
        if (increment_y > 0 && increment_y < data->minimap.height && increment_x > 0 && increment_x < data->minimap.width)
            custom_mlx_pixel_put(&data->minimap_img, increment_x, increment_y, 0x00FF00);
        increment_y +=  data->player.factor_y;
        increment_x +=  data->player.factor_x;
        i++;
    }
}

void    minimap_pov(t_all_data *data)
{
    dda(data);
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
    mini_map(&data, data.cu_map, true);
    initial_endpoint(&data);
    re_calculate_factors(&data);
    minimap_pov(&data);
    game(&data.game_img);
    put_images_to_window(&data);
    mlx_hook(data.mlx.window, 17, 0, close_btn, &data.mlx);
    mlx_hook(data.mlx.window, 2, 0, key_hook, &data);
    mlx_loop(data.mlx.connection);
}