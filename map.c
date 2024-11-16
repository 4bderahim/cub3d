#include "cubed.h"

char *next_line(int fd, int len)
{
    int i;
    int rt;
    char *line;
    char *next_line;
    char *tmp;

    i = 0;
    rt = 1;
    next_line = (char *)malloc(1);
    if (!next_line)
        return (NULL);
    next_line[0] = 0;
    int te;
    while (rt)
    {
        line = (char *)ft_calloc(len + 1, sizeof(char));
        rt = read(fd, line, len);
        if (rt == -1)
            exit(1);
        if (rt == 0 && ft_strlen(next_line) == 0)
        {
            return (NULL);
        }
        if (rt == 0 || (len == 1 && *line == '\n'))
        {
            free(line);
            break;
        }
        tmp = next_line;
        next_line = ft_strjoin(next_line, line);
        i++;
        free(tmp);
        free(line);
    }
    return (next_line);
}
char *line(char *s)
{
    int i;
    i = 0;

    while (s[i])
    {
        if (s[i] == '\n')
        {
            s[i] = 0;
            return (s);
        }
        i++;
    }
    return (NULL);
}

int len_(char *s)
{
    int i;
    int j;

    j = 0;
    i = 0;
    while (s[i])
    {
        if (s[i] == ',' && s[i + 1] != 0)
            j++;
        if (s[i] == ',' && (i == 0 || s[i + 1] == ','))
            return (0);
        i++;
    }
    if (j == 2)
        return (1);
    return (0);
}
int get_index(char *s)
{
    int i;

    i = 0;
    while (s[i] && s[i] != ',')
        i++;
    return (i);
}

int set_fr_fg_fb(t_cu *cu, char *s, int x)
{
    int i;
    i = 0;

    i = get_index(s);
    s[i] = '\0';
    if (x)
        cu->fr = atoi(s);
    else
        cu->cr = atoi(s);
    s = s + i + 1;
    i = get_index(s);
    s[i] = 0;
    if (x)
        cu->fg = atoi(s);
    else
        cu->cg = atoi(s);
    s = s + i + 1;
    if (x)
        cu->fb = atoi(s);
    else
        cu->cb = atoi(s);
    return (1);
}

int set_fc__(t_parsed_data *data_set, char *str , t_cu *cu, char c)
{
    if (str[data_set->i + 1] != ' ' || str[data_set->i + 2] == 0 || !len_(str + 2))
        return (0);
    if (c == 'F')
        {
            if (data_set->f == 1)
                return (0);
            set_fr_fg_fb(cu, str + data_set->i + 2, 0);
            data_set->f = 1;
        }
    else
        {
            if ( data_set->c == 1)
                return (0);
            set_fr_fg_fb(cu, str + data_set->i + 2, 1);
            data_set->c = 1;
        }
    return (1);
}

int set_news__(char *str, char c, int index_num, t_parsed_data *data_set, char **news)
{
    
    if (str[data_set->i + 2] != ' ' || data_set->nb[index_num] == '1')
        return (0);
    news[index_num] = ft_strdup(str + data_set->i);
    data_set->nb[index_num] = '1';
    return (1);
}
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
int parse_fc(t_parsed_data *data_set, char *str, t_cu *cu)
{
    if (str[data_set->i] == 'F')
    {
        if (!set_fc__(data_set, str, cu, 'F'))
            return (0);
    }
    else if (str[data_set->i] == 'C')
    {
        if (!set_fc__(data_set, str, cu, 'C'))
            return (0);
    }
    return (1);
}

int parse_news(t_parsed_data *data_set, char **news, char *str)
{
    if (str[data_set->i] == 'N')
    {
        if (str[data_set->i + 1] != 'O')
            return (0); 
        if (!set_news__(str, 'N', 0, data_set, news) )
            return (0);
    }
    else if (str[data_set->i] == 'E')
    {
        if (str[data_set->i + 1] != 'A')
            return (0);
        if (!set_news__(str, 'E', 1, data_set, news))
            return (0);
    }
    else if (str[data_set->i] == 'W')
    {
        if (str[data_set->i + 1] != 'E')
            return (0); 
        if (!set_news__(str, 'W', 2, data_set, news) )
            return (0);
    }
    else if (str[data_set->i] == 'S')
    {
        if (!set_news__(str, 'S', 3, data_set, news) )
            return (0);
    }
    return (1);
}

int check_map__cf_news(t_parsed_data *data_set, char **news, char *str, t_cu *cu)
{
    if (str[data_set->i] == 'F' || str[data_set->i] == 'C' 
        || str[data_set->i] == 'N' || str[data_set->i] == 'E'
        || str[data_set->i] == 'W' || str[data_set->i] == 'S')
    {
        if (str[data_set->i] == 'F' || str[data_set->i] == 'C')
        {
            if (!parse_fc(data_set, str, cu))
                return (0);
        }
        else
        {
            if (!parse_news(data_set , news, str))
                return (0);
        }
    }
    else if (str[data_set->i] == '1')
        return (-1);
    else
    {
        if (*(str + data_set->i) != '\0')
            return (0);
    }
    return (1);
}
char ** set_parsed_data(t_parsed_data data_set, int *map_check_ret)
{
    char **news;

    news = (char **)malloc(sizeof(char *) * 5);
    if (!news)
        return (NULL);
    news[4] = NULL;
    data_set.i = 0;
    data_set.c = 0;
    data_set.f = 0;
    *map_check_ret = 0;
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

char *fill_(char *s, int index, int map_index)
{
    int i;
    char *new;

    // printf("\n\t---%d|%d\n\n\n", index, map_index);
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

    // printf("%s\n\n\n", s+i);
    while (s[i] != '\n')
    {
        // printf("%c|\n\n\n\n\n", s[i]);
        if (s[i] != ' ')
            return (0);
        if (i == 0)
            break;
        i--;
    }
    return (1);
}
char **alloc_map(char *str)
{
    int i;
    int j;
    int cnt;
    char **map;
    int x;

    i = 0;
    x = 0;
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
    str = str + i;
    cnt = count_len(str);
    if (cnt == -1)
        return (NULL);
    map = (char **)malloc(sizeof(char *) * (cnt + 1));
    map[cnt] = NULL;
    if (!map)
        return (NULL);
    j = 0;
    i = 0;
    while (str[i])
    {
        x = 0;
        if (str[i] == '\n' || str[i + 1] == 0)
        {
            map[j] = fill_(str, i, j);
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
        return (NULL); // exit / error.

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
int not_walled(char **map)
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
    {
        // free all
        return (1);
    }
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

void free___(t_cu *map, int st)
{
    int i;
    i = 0;
    if (st == 1)
    {
        free(map);
    }
    else if (st == 2)
    {
        free(map->news[0]);
        free(map->news[1]);
        free(map->news[2]);
        free(map->news[3]);
    }
    else
    {
        while (map->map[i])
        {
            free(map->map[i]);
            i++;
        }
    }
    write(2, "error\ninvalid map!\n", 19);
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
    if (!cu->map)
    {
        free___(cu, 2);
        exit(1);
    }
    int i = 0;
    while (cu->map[i])
    {
        // printf("[%s]\n", cu->map[i]);
        i++;
    }
    i = 0;
   
    
    if (not_walled(cu->map) || !correct_map(cu->map))
    {
        free___(cu, 3);
        exit(1);
    }
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