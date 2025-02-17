#include "../cubed.h"

int set_news__(char *str, char c, int index_num, t_parsed_data *data_set, char **news)
{
    (void)c;
    int i;

    i = data_set->i + 2;

    while (str[i] && str[i] == ' ')
        i++
        ;
    if (str[i] == 0 || str[i] == '\n')
        return (0);
    if (str[data_set->i + 2] != ' ' || data_set->nb[index_num] == '1')
        return (0);
    news[index_num] = ft_strdup(str + data_set->i);
    data_set->nb[index_num] = '1';
    return (1);
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
        if (str[data_set->i + 1] != 'O' || !set_news__(str, 'N', 0, data_set, news))
            return (0); 
    }
    else if (str[data_set->i] == 'E')
    {
        if (str[data_set->i + 1] != 'A' || !set_news__(str, 'E', 1, data_set, news))
            return (0);
    }
    else if (str[data_set->i] == 'W')
    {
        if (str[data_set->i + 1] != 'E' || !set_news__(str, 'W', 2, data_set, news))
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
char **set_parsed_data(t_parsed_data *data_set, int *map_check_ret)
{
    char **news;

    news = (char **)malloc(sizeof(char *) * 5);
    if (!news)
        return (NULL);
    news[4] = NULL;
    data_set->i = 0;
    data_set->c = 0;
    data_set->f = 0;
    *map_check_ret = 0;
    return (news);
}