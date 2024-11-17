
#include "cubed.h"

int get_i_index(char **map, char *str )
{
    int i;
    int j;

    j = 0;
    i = 0;

    while (str[i])
    {
        if (str[i] == '1' && map_beg(str, i - 1))
        {
            while (str[i] != '\n')
                i--;
            i++;
            break;
        }
        i++;
    }
    return (i);
}

char ** alloc_full_map(char *str)
{
    char **map;
    int cnt;

    cnt = count_len(str);
    if (cnt == -1)
        return (NULL);
    map = (char **)malloc(sizeof(char *) * (cnt + 1));
    map[cnt] = NULL;
    if (!map)
        return (NULL);
    return (map);
}

char **alloc_map(char *str)
{
    int i;
    int j;
    char **map;

    str = str + get_i_index(map, str);
    map =  alloc_full_map(str);
    j = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == '\n' || str[i + 1] == 0)
        {
            map[j] = fill_(str, i);
            if (str[i + 1] == 0)
                break;
            j++;
            str = str + i + 1;
            i = -1;
        }
        i++;
    }
    return (map);
}

char **get_map__(char *str)
{
    int len;
    int i;
    char **map;

    i = ft_strlen(str) - 1;
    while (i >= 0 && (str[i] == ' ' || str[i] == '\n'))
        i--;
    if (str[i - 1] != '1')
        return (NULL);
    str[i + 1] = 0;
    i = 0;
    len = ft_strlen(str);
    while (str[i])
    {
        if (str[i] == '1')
        {
            map = alloc_map(str);
            if (!map)
                return (NULL);
            free(str);
            break;
        }
        i++;
    }
    return (map);
}

char **get_map(int fd)
{

    char **map;
    char *str;

    str = next_line(fd, 51);
    map = get_map__(str);
    if (!map)
        return (NULL);
    return (map);
}