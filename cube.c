#include "cubed.h"

static mlx_image_t* image;

// void height_width(t_cu *cu)
// {
//     int i;
//     int j;
//     char **map;
//     map = cu->map;
//     i = 0;
//     pr_max = 0;
//     while (map[i])
//     {
//         j = 0;
//         while (map[i][j])
//             {

//                 j++;
//             }
        
//         i++;
//     }
//     cu->map_width = j-1;
//     cu->map_height = i-1;
// }

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	(void)param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
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


int main()
{

    t_cu *cu_map;
    mlx_t *mlx;
    cu_map = fetch__();
    if (cu_map)
        return (0);
    height_width(cu_map);
    mlx = mlx_init(cu_map->map_width, cu_map->map_height, "trwaDi", NULL );
    if (!mlx)
        return (0);


	if (!(image = mlx_new_image(mlx, 128, 128)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
    // mlx_loop_hook(mlx, ft_randomize, mlx);
    mlx_loop(mlx);
    
}