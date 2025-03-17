
#include "../cubed.h"

int get_i_index(char **map, char *str )
{
    (void)map;
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

char **alloc_map(char *str)
{
    int i;
    int j;
    char **map = NULL;

    str = str + get_i_index(map, str);
    map =  alloc_full_map(str);

    int t;
    t = 0;
   
    j = 0;
    i = 0;

    //-------prob

    printf("\t\t\t|%s|\n");
    while (str[i])
    {
        if (str[i] == '\n' || str[i + 1] == 0)
        {
            int d;
            d = 0;
            printf(">>>>>>>>>>>\n");
            while (d < i)
            {
                printf("%c", str[d]);
                d++;
            }
            map[j] = fill_(str, i);

            if (str[i + 1] == 0)
                break;
            j++;
            str = str + i + 1;
            i = -1;
        }
        i++;
    }
    // int y = 0;
    //  while (map[t])
    // {
    //     y = 0;
    //     while (map[t][y])
    //     {
    //         printf("%c|", map[t][y]);

    //         y++;
    //     }
    //     printf("\n");
    //     t++;
    // }
    
    return (map);
}

char **get_map__(char *str)
{
    int len;
    int i;
    char **map = NULL;

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