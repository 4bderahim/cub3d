#include "../cubed.h"

char **last_news_cf_checkes(t_parsed_data data_set,char *str, char **news)
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
    t_parsed_data data_set ;
    char **news;
    int map_check_ret;
    char *str;

    news = set_parsed_data(&data_set, &map_check_ret);
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



t_cu *fetch__()
{
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
    printf("%d@@@@@@@@@@%d<<<\n\n", pr_max,j );
    cu->map_width = j;
    cu->map_height = i;
}
