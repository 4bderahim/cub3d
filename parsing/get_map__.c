#include "../cube.h"

int not_valid(int i, int j, int map_len , char **map)
{
    int line_len;

    line_len = 0;
    if (map[i][j] != '1' && map[i][j] != ' ')
            return (1);
        line_len = ft_strlen(map[i]) - 1;
        while (map[i][line_len] == ' ')
            line_len--;
        if (map[i][line_len] != '1')
            return (1);
    if (i == 0 || i == map_len - 1)
    {
        while (map[i][j])
        {
            if (map[i][j] != '1' && map[i][j] != ' ')
                return (1);
            j++;
        }
    }
    return (0);
}

int free_all(t_cu *map)
{
    int i;
    i = 0;

    free(map->news[0]);
    free(map->news[1]);
    free(map->news[2]);
    free(map->news[3]);
    while (map->map[i])
    {
        free(map->map[i]);
        i++;
    }
    free(map->map);
    free(map->news);
    free___(map, 1);
    return (1);
}

int not_walled(char **map, t_cu *cu)
{
    (void)cu;
    int i;
    int j;
    int map_len;
    
    map_len = 0;
    i = 0;
    while (map[map_len])
        map_len++;
    while (map[i])
    {
        j = 0;
        while (map[i][j] == ' ')
            j++;
        if (!map[i][j])
        {
            i++;
            continue;
        }
        if (not_valid(i, j,map_len, map))
            return (1);
        i++;
    }
    if (!check_map(map))
        return (1);
    return (0);
}

int correct_map(char **map)
{
    int i;
    int j;
    int x;

    i = 0;
    x = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if ((map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'S'))
            {
                if (x)
                    return (0);
                x = 1;
            }
            j++;
        }
        i++;
    }
    return (1);
}

void check_not_walled_map(t_cu *cu)
{
    if (!cu->map)
    {
        free___(cu, 2);
        exit(1);
    }
    if (not_walled(cu->map, cu) || !correct_map(cu->map))
    {
        free_all(cu);
        // free___(cu, 3);
        exit(1);
    }
}