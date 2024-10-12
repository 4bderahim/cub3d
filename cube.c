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

void dda(t_all_data *data)
{
    int i = 0;
    float increment_x = data->player.x+3;
    float increment_y = data->player.y+2;

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


int	key_check(int key)
{
    if (key == 0 || key == 1 || key == 2 || key == 13
        || key == 123 || key == 124)
    {
        return (1);
    }
    return (0);
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
    // recalculate endpoint pov line
    re_pov(keycode, data);

    // recalculate increment factors
    re_calculate_factors(data);

    // re-position player
    re_position_player(keycode, data);

    mini_map(data, data->cu_map, false);

    // redraw line
    minimap_pov(data);

    put_images_to_window(data);
    return (0);
}

void cast_ray(float ray_angle, int i , t_all_data *data)
{
    //
}
void cast_rays(t_all_data *data)
{
    float ray_angle;
    int i;

    i = 0;
    ray_angle = data->player.player_angle_rad  -(data->player.fov_angle / 2);
    while (i < N_RAYS )
    {
        cast_ray(ray_angle, i, data);
        ray_angle += data->player.fov_angle / N_RAYS;
        i++;
    }
    

}

void init_rays(t_all_data *data)
{
    t_ray **rays;
    int i;
    int r_num;

    data->rays = (t_ray **) malloc(sizeof(t_ray *)*11);
    if (!rays)
        return ;
    i = 0;
    r_num = 10;
    while (i < 10)
    {
        data->rays[i]->ray_angle = data->player.player_angle_rad / r_num ; 
        data->rays[i]->distance = 0;
        data->rays[i]->wall_y = 0;
        data->rays[i]->wall_x = 0;
        data->rays[i]->ray_left = 0;
        data->rays[i]->ray_down = 0;
        data->rays[i]->ray_right = 0;
        data->rays[i]->ray_up = 0;
        data->rays[i]->verical_hit = 0;
        i++;
    }

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
    data.player.fov_angle = 60 - (90 * to_deg);
    mini_map(&data, data.cu_map, true);
    initial_endpoint(&data);
    re_calculate_factors(&data);
    minimap_pov(&data);
    // init_rays(&data);
    
    // rays_(&data);
    game(&data.game_img);
    put_images_to_window(&data);
    mlx_hook(data.mlx.window, 17, 0, close_btn, &data.mlx);
    mlx_hook(data.mlx.window, 2, 0, key_hook, &data);
    mlx_loop(data.mlx.connection);
}