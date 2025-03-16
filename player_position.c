#include "cubed.h"

int get_player_direction(char c)
{
    if (c == 'N' || c == 'S' || c == 'E' ||  c==  'W')
        return c;
    return 0;
}

void    player_position(t_all_data *data, t_cu *cu_map)
{ 
    int i = 0;
    int j = 0;
    int tile_x = 0;
    int tile_y = 0;
    int direction = 0;

    data->player.fov_angle = 60 * to_rad;
    while (cu_map->map[i])
    {
        tile_y = i * data->minimap.tile;
        j = 0;
        while (cu_map->map[i][j])
        {
            tile_x = j * data->minimap.tile;
            direction = get_player_direction(cu_map->map[i][j]);
            if (direction)
            {
                data->player.direction = direction;
                data->player.x = tile_x;
                data->player.y = tile_y;
            }
            j++;
        }
        i++;
    }
}