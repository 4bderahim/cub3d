#include "cubed.h"

char ** last_news_cf_checkes(t_parsed_data data_set,char *str, char **news)
{
    if (!data_set.f || !data_set.c)
        return (NULL);
    data_set.i = 0;
    while (data_set.i < 4)
    {
        if (data_set.nb[data_set.i] != '1')
            return (NULL);
        data_set.i++;
    }
    free(str);
    return (news);
}

char **set_fc(int fd, t_cu *cu)
{
    t_parsed_data data_set;
    char **news;
    int map_check_ret;
    char *str;

    news = set_parsed_data(data_set, &map_check_ret);
    if (!news)
        return (NULL);
    while (1)
    {
        str = next_line(fd, 1);
        if (!str)
            break;
        data_set.i = 0;
        while (str[data_set.i] && str[data_set.i] == ' ')
            data_set.i++;
        map_check_ret =  check_map__cf_news(&data_set, news, str, cu);
        if (!map_check_ret)
            return (NULL);
        if (map_check_ret == -1)
            break;
        free(str);
    }
    return (last_news_cf_checkes(data_set, str, news));
}

int player_char(char c, char *s, int i)
{
    int ii;
    char *str;
    int x;

    x = 0;
    str = "NSEWFC";
    ii = 0;
    while (str[ii])
    {
        if (str[ii] == c)
        {
            x = 1;
            if ((s[i - 1] != '1' && s[i - 1] != '0') || (s[i + 1] != '1' && s[i + 1] != '0'))
                return (0);
        }
        ii++;
    }
    if (!x)
        return (0);
    return (1);
}

size_t count_len(char *s)
{
    int count;

    count = 0;
    while (*(s))
    {
        if (*s == '\n')
        {
            if (*(s + 1) == '\n')
                return (-1);
            count++;
        }
        s++;
    }
    return (count + 1);
}

char *fill_(char *s, int index)
{
    int i;
    char *new;

    new = (char *)malloc(sizeof(char) * (index + 1));
    if (!new)
        exit(1);
    new[index] = 0;
    i = 0;
    while (i < index)
    {
        new[i] = s[i];
        i++;
    }
    return (new);
}

int map_beg(char *s, int i)
{
    while (s[i] != '\n')
    {
        if (s[i] != ' ')
            return (0);
        if (i == 0)
            break;
        i--;
    }
    return (1);
}

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

int check_map(char **map)
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == '0')
            {
                if (!map[i][j + 1] || map[i][j + 1] == ' ' || j == 0 || map[i][j - 1] == ' ')
                    return (0);
                if (j >= ft_strlen(map[i + 1]) || map[i + 1][j] == ' ')
                    return (0);
                if (j >= ft_strlen(map[i - 1]) || map[i - 1][j] == ' ')
                    return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

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
    free___(map, 3);
    free___(map, 2);
    free___(map, 1);
    return (1);
}

int not_walled(char **map, t_cu *cu)
{
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
        return (free_all(cu));
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
        free___(cu, 3);
        exit(1);
    }
}

t_cu *fetch__()
{
    char **str;
    char *s;
    t_cu *cu;
    int fd, f;

    cu = (t_cu *)malloc(sizeof(t_cu));
    fd = open("./x.cube", O_RDWR);
    if (!fd)
        return (0);
    f = open("./x.cube", O_RDWR);
    cu->news = set_fc(f, cu);
    if ((cu->news) == NULL)
    {
        free___(cu, 1);
        return (0);
    }
    close(f);
    fd = open("./x.cube", O_RDWR);
    cu->map = get_map(fd);
    check_not_walled_map(cu);
    return (cu);
}

void height_width(t_cu *cu)
{
    int i;
    int j = 0;
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
    cu->map_width = pr_max;
    cu->map_height = i;
}
