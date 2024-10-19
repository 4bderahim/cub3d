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

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}


void    celine_and_floor(t_all_data *data)
{
    int celine_color = create_rgb(data->cu_map->cr, data->cu_map->cg, data->cu_map->cb);
    int floor_color = create_rgb(data->cu_map->fr, data->cu_map->fg, data->cu_map->fb);

    int i = 0;
    //celine
    while (i < WIDTH)
    {
        int j = 0;
        while (j < HEIGHT / 2)
        {
            custom_mlx_pixel_put(&data->game_img, i, j, celine_color);
            j++;
        }
        i++;
    }

    // floor
    i = 0;
    while (i < WIDTH)
    {
        int j = HEIGHT / 2;
        while (j < HEIGHT)
        {
            custom_mlx_pixel_put(&data->game_img, i, j, floor_color);
            j++;
        }
        i++;
    }
}

#define thickness WIDTH / N_RAYS 

void    print_wall(t_all_data *data, float wall_height, int starting_x, int starting_y, int index_, int img_bpp, char *data_addr, double tex_pos, double step)
{
    int i = 0;

    int x;
    x= 0;
    printf("%d\n\n", thickness);
    // while (i < thickness)
    // {
    int j = 0;
    
    while (j < wall_height )
    {
        int tex_y = (int)tex_pos & (512 - 1);  // Texture Y coordinate (loops if necessary)

    // Sample pixel from texture
        // printf("\t\t\t|%d|\n", index_);
        int color = *(int *)(data_addr + (index_+(j+4)));
        float x = starting_x + i;
        float y = starting_y + j;
        // printf("\t\t\t||%d|||\n", color);
        if (y >= 0 && y <= HEIGHT && x >= 0 && x <= WIDTH)
        {
            //if (j%2 == 0)
            custom_mlx_pixel_put(&data->game_img, x, y, color);
           // else
            // /    custom_mlx_pixel_put(&data->game_img, x, y, 0x808080);
        }
        j++;
        // }
        // i++;
    }
}

void    game(t_all_data  *data)
{
    celine_and_floor(data);
    void *mlx;
    
    int     index__;
    index__ =   0;
    int		img_bpp ;
	int		img_height ;
    int endian;
    void *img = mlx_xpm_file_to_image(data->mlx.connection, "./dun.xpm", &img_bpp,&img_height); 
    char *data_addr = mlx_get_data_addr( img, &img_bpp, &img_height, &endian);
    // mlx_ 933241 885022
    int i = 0;
    while (i < N_RAYS)
    {
        float to_projection_plan = (WIDTH / 2) / tan(data->player.fov_angle / 2);
        float sanitized_distance = data->rays[i].distance * cos(data->rays[i].ray_angle - data->player.player_angle_rad);
        float wall_height = (data->minimap.tile / sanitized_distance) * to_projection_plan;
        double step = 0;//(double)HEIGHT / wall_height;
        double tex_pos = 0;//((((HEIGHT / 2) - (wall_height / 2)) - HEIGHT) / 2 + wall_height / 2) * step;
        print_wall(data, wall_height, i * thickness, (HEIGHT / 2) - (wall_height / 2), index__, img_bpp, data_addr, tex_pos, step);
        // index__ += (wall_height);
        i++;
    }
}

void minimap_calcs(t_all_data *data, t_cu *cu_map)
{
    data->minimap.tile = 20;
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


void    horizontal_intersection(t_all_data *data, t_direction direction, t_rays_utils *horizontal, float ray_angle)
{
    float x_check = 0;
    float y_check = 0;

    horizontal->y_hit = (int)(data->player.y / data->minimap.tile) * data->minimap.tile;
    if (direction.down)
        horizontal->y_hit += data->minimap.tile;
    // x
    horizontal->x_hit = data->player.x + ((horizontal->y_hit - data->player.y) / tan(ray_angle));    

    // horizonal x & y steps
    // y
    horizontal->y_step = data->minimap.tile;
    if (direction.up)
        horizontal->y_step *= -1;
    // x
    horizontal->x_step = data->minimap.tile / tan(ray_angle);
    if (direction.left && horizontal->x_step > 0)
        horizontal->x_step *= -1;
    if (direction.right && horizontal->x_step < 0)
        horizontal->x_step *= -1;

    // search for intersection
    while (horizontal->x_hit > 0 && horizontal->x_hit < data->minimap.width && horizontal->y_hit > 0 && horizontal->y_hit < data->minimap.height)
    {
        x_check = horizontal->x_hit;
        y_check = horizontal->y_hit;
        if (direction.up)
            y_check = horizontal->y_hit - 1;
        if (data->cu_map->map[(int)(y_check / data->minimap.tile)][(int)(x_check / data->minimap.tile)] == '1')
            break;
        horizontal->x_hit += horizontal->x_step;
        horizontal->y_hit += horizontal->y_step;
    }
}

void    vertical_intersection(t_all_data *data, t_direction direction, t_rays_utils *vertical, float ray_angle)
{
    float x_check = 0;
    float y_check = 0;

    // intersection
    // x
    vertical->x_hit = (int)(data->player.x / data->minimap.tile) * data->minimap.tile;
    if (direction.right)
        vertical->x_hit += data->minimap.tile;
    // y
    vertical->y_hit = data->player.y + ((vertical->x_hit - data->player.x) * tan(ray_angle));
    
    // vertical x & y steps
    // x
    vertical->x_step = data->minimap.tile;
    if (direction.left)
        vertical->x_step *= -1;
    // y
    vertical->y_step = data->minimap.tile * tan(ray_angle);
    if (direction.up && vertical->y_step > 0)
        vertical->y_step *= -1;
    if (direction.down && vertical->y_step < 0)
        vertical->y_step *= -1;
    
    // search for intersection
    while (vertical->x_hit > 0 && vertical->x_hit < data->minimap.width && vertical->y_hit > 0 && vertical->y_hit < data->minimap.height)
    {
        x_check = vertical->x_hit;
        if (direction.left)
            x_check = vertical->x_hit - 1;
        y_check = vertical->y_hit;
        if (data->cu_map->map[(int)(y_check / data->minimap.tile)][(int)(x_check/data->minimap.tile)] == '1')
            break;
        vertical->x_hit += vertical->x_step;
        vertical->y_hit += vertical->y_step;
    }
}

void cast_ray(float ray_angle, int i, t_all_data *data)
{
    t_direction direction;
    t_rays_utils horizontal;
    t_rays_utils vertical;
        
    ray_angle = angle_fix(ray_angle);
    

    //set ray direction
    set_direction(&direction, ray_angle);
    
    horizontal_intersection(data, direction, &horizontal, ray_angle);
    vertical_intersection(data, direction, &vertical, ray_angle);
    
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
    float pov = 0;
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
    float dx = ray_x - data->player.x ;
    float dy = ray_y - data->player.y ;
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
        // custom_mlx_pixel_put(&data->minimap_img, data->rays[i].wall_x, data->rays[i].wall_y,  0xFF0000);
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
    game(data);
    put_images_to_window(data);
    return (0);
}
// void	img_pix_put(void *img, int x, int y, int color)
// {
//     char    *pixel;

//     pixel = img-> addr + (y * img->line_len + x * (img->bpp / 8));
//     *(int *)pixel = color;
// }
// int render_rect(void *img)
// {
//     int	i;
//     int j = 20;

//     i =  10;
//     while (i < 10)
//     {
//         while (j <  20)
//             img_pix_put(img, j++, i,  0xfff0000);
//         ++i;
//     }
//     return (0);
// }

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
    game(&data);
    
    // printf("\t%d||%d|\n", img_height, img_width);

    // mlx_get_data_addr()
    // mlx_put_image_to_window(data.mlx.connection, data.mlx.window, img, 0, 0);
    put_images_to_window(&data);
    mlx_hook(data.mlx.window, 17, 0, close_btn, &data.mlx);
    mlx_hook(data.mlx.window, 2, 0, key_hook, &data);
    mlx_loop(data.mlx.connection);
}