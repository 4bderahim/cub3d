#include "../cube.h"


int cf_news_exist(char c)
{
   if (c != 'F' || c != 'C' 
        || c != 'N' || c != 'E'
        || c != 'W' || c != 'S')
            return (-1);
    if (c == 'F' || c == 'C' 
        || c == 'N' || c == 'E'
        || c == 'W' || c == 'S')
            return (1);
    return (0);
}

int cf_news__(t_parsed_data *data_set, char **news, char *str, t_cu *cu)
{
     if (str[data_set->i] == 'F' || str[data_set->i] == 'C')
        {
            if (!parse_fc(data_set, str, cu))
            {
                free_news(data_set, news);
                return (0);
            }
        }
        else
        {
            if (!parse_news(data_set , news, str))
            {
                free_news(data_set, news);
                return (0);
            }
        }
    return (1);

}
int check_map__cf_news(t_parsed_data *data_set, char **news, char *str, t_cu *cu)
{

    if (!cf_news_exist(str[data_set->i]))
       {
                free_news(data_set, news);
                return (0);
            }
    if (cf_news_exist(str[data_set->i]))
    {
        if (!cf_news__(data_set,  news ,  str, cu))
            return (0);
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