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
    angle = remainder(angle, M_PI * 2);
    if (angle < 0)
        angle = (M_PI * 2) + angle;
    return (angle);
}

float calculate__(float px, float py, float px_hit, float py_hit)
{
    return sqrt(pow(px_hit - px, 2) + pow(py_hit - py, 2));
}

typedef struct s_direction
{
    int up;
    int down;
    int right;
    int left;
} t_direction;

typedef struct s_rays_utils
{
    float x_hit;
    float y_hit;
    float x_step;
    float y_step;
    float distance;
} t_rays_utils;


void    set_direction(t_direction *direction, float ray_angle)
{
    direction->up = 0;
    direction->left = 0;
    if (ray_angle > 0 && ray_angle < M_PI)
        direction->up = 1;
    direction->down = !(direction->up);
    if (ray_angle < (M_PI / 2) || ray_angle > (M_PI + (M_PI / 2)))
        direction->left = 1;
    direction->right = !direction->left;
}


void cast_ray(float ray_angle, int i, t_all_data *data)
{
    t_direction direction;
    t_rays_utils horizontal;
    t_rays_utils vertical;
    
    float x_check;
    float y_check;
        
    ray_angle = angle_fix(ray_angle);
    
    //set ray direction
    set_direction(&direction, ray_angle);

    // intersection coordinates
    // y
    horizontal.y_hit = (int)(data->player.y / data->minimap.tile) * data->minimap.tile;
    if (direction.down)
    {
        horizontal.y_hit += data->minimap.tile;
    }
    // x
    horizontal.x_hit = data->player.x + ((horizontal.y_hit - data->player.y) / tan(ray_angle));    

    // horizonal x & y steps
    // y
    horizontal.y_step = data->minimap.tile;
    if (direction.up)
        horizontal.y_step *= -1;
    // x
    horizontal.x_step = data->minimap.tile / tan(ray_angle);
    if (direction.left && horizontal.x_step > 0)
        horizontal.x_step *= -1;
    if (direction.right && horizontal.x_step < 0)
        horizontal.x_step *= -1;

    // search for intersection
    while (horizontal.x_hit > 0 && horizontal.x_hit < data->minimap.width && horizontal.y_hit > 0 && horizontal.y_hit < data->minimap.height)
    {
        x_check = horizontal.x_hit;
        y_check = horizontal.y_hit;
        if (direction.up)
            y_check = horizontal.y_hit - 1;
        if (data->cu_map->map[(int)(y_check / data->minimap.tile)][(int)(x_check / data->minimap.tile)] == '1')
            break;
        horizontal.x_hit += horizontal.x_step;
        horizontal.y_hit += horizontal.y_step;
    }

    //VERTICAL



    // intersection
    // x
    vertical.x_hit = (int)(data->player.x / data->minimap.tile) * data->minimap.tile;
    if (direction.right)
        vertical.x_hit += data->minimap.tile;
    // y
    vertical.y_hit = data->player.y + ((vertical.x_hit - data->player.x) * tan(ray_angle));
    
    // vertical x & y steps
    // x
    vertical.x_step = data->minimap.tile;
    if (direction.left)
        vertical.x_step *= -1;
    // y
    vertical.y_step = data->minimap.tile * tan(ray_angle);
    if (direction.up && vertical.y_step > 0)
        vertical.y_step *= -1;
    if (direction.down && vertical.y_step < 0)
        vertical.y_step *= -1;
    
    // search for intersection
    while (vertical.x_hit > 0 && vertical.x_hit < data->minimap.width && vertical.y_hit > 0 && vertical.y_hit < data->minimap.height)
    {
        x_check = vertical.x_hit;
        if (direction.left)
            x_check = vertical.x_hit - 1;
        y_check = vertical.y_hit;
        if (data->cu_map->map[(int)(y_check / data->minimap.tile)][(int)(x_check/data->minimap.tile)] == '1')
            break;
        vertical.x_hit += vertical.x_step;
        vertical.y_hit += vertical.y_step;
    }
    
    // calculate and compare distances
    horizontal.distance = calculate__(data->player.x, data->player.y, horizontal.x_hit, horizontal.y_hit);
    vertical.distance = calculate__(data->player.x, data->player.y, vertical.x_hit, vertical.y_hit);
    if (vertical.distance < horizontal.distance)
    {
        data->rays[i].verical_hit = 1;
        data->rays[i].wall_x = vertical.x_hit;
        data->rays[i].wall_y = vertical.y_hit;
        data->rays[i].distance = vertical.distance;        
    }
    else
    {
        data->rays[i].verical_hit = 0;
        data->rays[i].wall_x = horizontal.x_hit;
        data->rays[i].wall_y = horizontal.y_hit;
        data->rays[i].distance = horizontal.distance;
    }
    data->rays[i].ray_left = direction.left; 
    data->rays[i].ray_right = direction.right;
    data->rays[i].ray_down = direction.down;
    data->rays[i].ray_up = direction.up;
    data->rays[i].ray_angle = ray_angle;
}

void cast_rays(t_all_data *data)
{
    int i = 0;
    float ray_angle = data->player.player_angle_rad - (data->player.fov_angle / 2);
    float angle_factor = data->player.fov_angle / N_RAYS;
    while (i < N_RAYS)
    {
        cast_ray(ray_angle, i++, data);
        ray_angle += angle_factor;
    }
}

void    ray_dda(t_all_data *data, float ray_x, float ray_y)
{
    int i = 0;
    float dx = ray_x - data->player.x;
    float dy = ray_y - data->player.y;
    float steps = 0;
    if (fabs(dx) >= fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);
    float factor_x = dx / steps;
    float factor_y = dy / steps;
    float increment_x = data->player.x;
    float increment_y = data->player.y;
    while (i < steps)
    {
        if (increment_y >= 0 && increment_y <= data->minimap.height && increment_x >= 0 && increment_x <= data->minimap.width)
            custom_mlx_pixel_put(&data->minimap_img, increment_x, increment_y, 0x00FF00);
        increment_x +=  factor_x;
        increment_y += factor_y;
        i++;
    }
}

void render__rays(t_all_data *data)
{
    int i = 0;
    while (i < N_RAYS)
    {
        ray_dda(data, data->rays[i].wall_x, data->rays[i].wall_y);
        // custom_mlx_pixel_put(&data->minimap_img, data->rays[i].wall_x, data->rays[i].wall_y,  0xFF0000);
        // custom_mlx_pixel_put(&data->minimap_img, data->rays[i].wall_x+1, data->rays[i].wall_y+1,  0xFF0000);
        // custom_mlx_pixel_put(&data->minimap_img, data->rays[i].wall_x+2, data->rays[i].wall_y+2,  0xFF0000);
        i++;
    }
}

void init_rays(t_all_data *data)
{
    int i = 0;

    data->rays = malloc(sizeof(t_ray) * N_RAYS);
    if (!data->rays)
        exit(1);    
    while (i < N_RAYS)
    {
        data->rays[i].ray_angle = data->player.player_angle_rad / N_RAYS; 
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
    re_pov(keycode, data);
    re_position_player(keycode, data);
    
    mini_map(data, data->cu_map, false); 
    free(data->rays);
    data->rays = NULL;

    init_rays(data);
    cast_rays(data);
    render__rays(data);
    
    // printf("player angle in degree: %d\n", data->player.player_angle_degree);
    // printf("player angle in radian: %f\n\n", data->player.player_angle_rad);
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
    data.player.fov_angle = 60 * to_rad;
    mlx_initial(&data.mlx, &data.minimap_img, &data.game_img, data.minimap);
    
    mini_map(&data, data.cu_map, true);
    initial_endpoint(&data);

    init_rays(&data);
    cast_rays(&data);
    render__rays(&data);

    game(&data.game_img);
    put_images_to_window(&data);
    mlx_hook(data.mlx.window, 17, 0, close_btn, &data.mlx);
    mlx_hook(data.mlx.window, 2, 0, key_hook, &data);
    mlx_loop(data.mlx.connection);
}