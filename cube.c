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
float angle_fix(float angle)
{
    angle = remainder(angle, M_PI*2);
    if (angle < 0)
        angle = (M_PI*2) + angle;
    return (angle);
}

float calculate__(float px,float py,float px_hit,float py_hit)
{
    return sqrt((px_hit - px) * (px_hit -px) * (py_hit -py )* (py_hit -py));
}

void cast_ray(float ray_angle, int i , t_all_data *data)
{
    int ray_up;
    int ray_down;
    int ray_right;
    int ray_left;
    float x_hit;
    float y_hit;
    float x_step;
    float y_step;
    //
    int horz_hit = false;
    float horz_hitx = 0;
    float horz_hity = 0;
    int horz_hit_content;
    float next_horz_x;
    float next_horz_y;

    float x_check;
    float y_check;

    ray_angle = angle_fix(ray_angle);
    ray_down = 0;
    if (ray_angle > 0 && ray_angle < M_PI)
        {
            ray_down = 1;
        }
    ray_up = !(ray_down);
    ray_right = 0;
    if (ray_angle < (M_PI/2) || ray_angle > (M_PI+(M_PI/2)))
        ray_right = 1;
    ray_left = !ray_right;
    y_hit = floor(data->player.y/ data->minimap.tile) * data->minimap.tile;
    if (ray_down)
        y_hit += data->minimap.tile;
    x_hit = data->player.x + (y_hit - data->player.y) / tan(ray_angle);
    y_step = data->minimap.tile;
    if (ray_up)
        y_step *= -1;
    x_step = data->minimap.tile / tan(ray_angle);
    if (ray_left && x_step > 0)
        x_step *= -1;
    if (ray_right && x_step < 0)
        x_step *= -1;
    next_horz_x = x_hit;
    next_horz_y = y_hit;
    while (next_horz_x >= 0 && next_horz_x <= data->minimap.width && next_horz_y >= 0 && next_horz_y <= data->minimap.height)
    {
        x_check = next_horz_x;
        y_check = next_horz_y + (ray_up ? -1: 0);
        // if (ray_up)
        //     y_check -= 1;
        if (data->cu_map->map[(int)floor(y_check / data->minimap.tile)][(int)floor(x_check/data->minimap.tile)] == '1')
        {
            horz_hitx = next_horz_x;
            horz_hity = next_horz_y;
            horz_hit = true;
            // 
            break;
        }
        else
        {
            next_horz_x += x_step;
            next_horz_y += y_step;
        }
    }

    // int vert_hit = false;
    // float vert_hitx = 0;
    // float vert_hity = 0;
    // int vert_hit_content;
    // float next_vert_x;
    // float next_vert_y;

    // // float x_check;
    // // float y_check;
  
    // x_hit = floor(data->player.y/ data->minimap.tile) * data->minimap.tile;
    // if (ray_down)
    //     x_hit += data->minimap.tile;
    // y_hit = data->player.y + (x_hit - data->player.x) * tan(data->rays[i].ray_angle );
    // x_step = data->minimap.tile;
    // if (ray_up)
    //     x_step *= -1;
    // y_step = data->minimap.tile / tan(data->rays[i].ray_angle) ;
    // if (ray_left && y_step > 0)
    //     y_step *= -1;
    // if (ray_right && y_step < 0)
    //     y_step *= -1;
    // next_vert_x = x_hit;
    // next_vert_y = y_hit;
    // while (next_vert_x >= 0 && next_vert_x <= data->minimap.height && next_vert_y >= 0 && next_vert_y <= data->minimap.height)
    // {
    //     x_check = next_vert_x;
    //     y_check = next_vert_x;
    //     if (ray_up)
    //         x_check -= 1;
    //     if (data->cu_map->map[(int)y_check / data->minimap.tile][(int)x_check/data->minimap.tile] == '1')
    //     {
    //         vert_hitx = next_vert_x;
    //         vert_hity = next_vert_y;
    //         vert_hit = true;
    //         // 
    //         break;
    //     }
    //     next_vert_x += x_step;
    //     next_vert_y += y_step;
    // }
    float  horz_dist ;
    float  vert_dist ;

    horz_dist = 100000;
    vert_dist = 100000;
    if (horz_hit)
        horz_dist = calculate__(data->player.x, data->player.y, x_hit, y_hit);
    // if (vert_hit)
    //     vert_dist = calculate__(data->player.x, data->player.y, x_hit, y_hit);
    // if (vert_dist < horz_dist)
    // {
    //     data->rays[i].distance = vert_dist;
    //     data->rays[i].verical_hit = 1;
    //     data->rays[i].wall_x = vert_hitx;
    //     data->rays[i].wall_y = vert_hity;
    // }
    // else
    // {
        data->rays[i].distance = horz_dist;
        data->rays[i].verical_hit = 0;
        data->rays[i].wall_x = horz_hitx;
        data->rays[i].wall_y = horz_hity;
    // }
    data->rays[i].ray_left = ray_left; 
    data->rays[i].ray_right = ray_right;
    data->rays[i].ray_down = ray_down;
    data->rays[i].ray_up = ray_up;
    data->rays[i].ray_angle = ray_angle;
}

void cast_rays(t_all_data *data)
{
    float ray_angle;
    int i;

    i = 0;
    ray_angle = data->player.player_angle_rad -  (60 * (M_PI / 180) / 2);
    while (i < N_RAYS )
    {
        cast_ray(ray_angle, i, data);
        ray_angle += (60 * (M_PI / 180)) / N_RAYS;
        i++;
    }
}
void put_pixel(t_all_data *data, int x, int y, int color) {
    mlx_pixel_put(data->minimap_img.addr ,data->minimap_img.img, x, y, color);
}

void draw_line(t_all_data *data, int x1, int y1, int x2, int y2, int color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        put_pixel(data, x1, y1, color); // Draw pixel at (x1, y1)

        if (x1 == x2 && y1 == y2) 
            break; // Line finished

        int err2 = err * 2;
        if (err2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (err2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}
void render__rays(t_all_data *data)
{
    int i;
    i = 1;
    // draw_line(data, data->player.x, data->player.y, data->rays[2].wall_x, data->rays[2].wall_y, 0x00FF00);

    while (i < N_RAYS )
    {
        // printf("\n@@@@@%f|%f|\n",data->rays[i].wall_x, data->rays[i].wall_y);
         draw_line(data, data->player.x, data->player.y, data->rays[i].wall_x, data->rays[i].wall_y,  0xFF0000);
        custom_mlx_pixel_put(&data->minimap_img, data->rays[i].wall_x, data->rays[i].wall_y,  0xFF0000);
        custom_mlx_pixel_put(&data->minimap_img, data->rays[i].wall_x+1, data->rays[i].wall_y+1,  0xFF0000);
        custom_mlx_pixel_put(&data->minimap_img, data->rays[i].wall_x+2, data->rays[i].wall_y+2,  0xFF0000);
       // break;
        i++;
    }
}

void init_rays(t_all_data *data)
{
    int i;
    int r_num;

    data->rays = malloc(sizeof(t_ray)*N_RAYS+1);
    if (!data->rays)
        return ;

    i = 1;
    r_num = N_RAYS;
    while (i < N_RAYS)
    {
        printf("\t\t\t||%d||\n\n\n", i);
        data->rays[i].ray_angle = data->player.player_angle_rad / N_RAYS ; 
        data->rays[i].distance = 0;
        data->rays[i].wall_y = 0;
        data->rays[i].wall_x = 0;
        data->rays[i].ray_left = 0;
        data->rays[i].ray_down = 0;
        data->rays[i].ray_right = 0;
        data->rays[i].ray_up = 0;
        data->rays[i].verical_hit = 0;
        i++;
    }
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
    free(data->rays);
    init_rays(data);
    cast_rays(data);
    render__rays(data);
    put_images_to_window(data);
    return (0);
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
    init_rays(&data);
    cast_rays(&data);
    render__rays(&data);
    game(&data.game_img);
    put_images_to_window(&data);
    mlx_hook(data.mlx.window, 17, 0, close_btn, &data.mlx);
    mlx_hook(data.mlx.window, 2, 0, key_hook, &data);
    mlx_loop(data.mlx.connection);
}