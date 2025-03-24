
#include "../cube.h"

int get_i_index(char **map, char *str)
{
    (void)map;
    int i;

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

char **alloc_full_map(char *str)
{
    char **map = NULL;
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

int max_len(char *s)
{

    int i;
    int x;
    i = 0;
    x = 0;
    while (s[i])
    {
        // printf("%d||%d||\n", i, x);
        if (s[i] == '\n' || s[i + 1] == '\0')
        {
            // printf("\t\t\t\t\t\t%d|--|%d\n\n", i, x);
            if ((x) < (i))
            {
                x = i;
            }
            s += i + 1;
            i = -1;
        }
        i++;
    }
    return (x);
}
char **alloc_map(char *str)
{
    int i;
    int j;
    char **map = NULL;
    int max_size;

    str = str + get_i_index(map, str);
    map = alloc_full_map(str);
    max_size = max_len(str);
    // printf("\t\t\t\t ########## %d \n\n\n" ,  max_size);
    j = 0;
    i = 0;
    // exit(1);

    while (str[i])
    {
        if (str[i] == '\n' || str[i + 1] == 0)
        {
            if (str[i + 1] == 0)
                map[j] = fill_(str, i + 1, max_size);
            else
                map[j] = fill_(str, i, max_size);
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
    int i;
    char **map = NULL;

    i = ft_strlen(str) - 1;
    while (i >= 0 && (str[i] == ' ' || str[i] == '\n'))
        i--;
    if (str[i - 1] != '1')
        return (NULL);
    str[i + 1] = 0;
    i = 0;
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