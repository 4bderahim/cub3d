#include "../cube.h"


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

int color_error(char *str)
{
    int i;

    i = 0;
    while (str[i] )
    {
        
        while (str[i])
        {
            i++;
        }
        
        if ((str[i] < '0' || str[i] > '9') && str[i] == ',')
            return (color_error(str+i+1));
        i++;
    }
    return (0);
}

int cf_color_not_valid(char *str)
{
    int i;
    i = 0;

    while (str[i] && str[i] != '\n')
    {
        if (str[i] < '0' || str[i] > '9')
        {
            if (!(str[i] >= 9 && str[i] <= 13) && str[i] != 32 && str[i] != '-' && str[i] != ',')
                return (1);
        }
        if (str[i] >= '0' && str[i] <= '9')
        {
            if (str[i+1] && str[i+1] == ' ')
                return (1);
        }
        i++;
    }
    return (0);
}

int set_fc__(t_parsed_data *data_set, char *str , t_cu *cu, char c)
{
    if (str[data_set->i + 1] != ' ' || str[data_set->i + 2] == 0 || !len_(str + 2))
        return (0);
    if (c == 'F')
    {
        if (data_set->f == 1 || cf_color_not_valid(str + data_set->i + 2))
            return (0);
        if (!set_fr_fg_fb(cu, str + data_set->i + 2, 1))
            return (0);
        data_set->f = 1;
        }
    else
    {
        if ( data_set->c == 1 || cf_color_not_valid(str + data_set->i + 2))
            return (0);
        if (!set_fr_fg_fb(cu, str + data_set->i + 2, 0))
            return (0);
        data_set->c = 1;
    }
    return (1);
}