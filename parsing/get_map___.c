#include "../cubed.h"
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

char *fill_(char *s, int index, int max )
{
    int i;
    char *new;

    new = (char *)malloc(sizeof(char) * (max + 1));
    if (!new)
        exit(1);
    new[max] = 0;
    i = 0;
    while (i < index)
    {
        new[i] = s[i];
        i++;
    }
    while (i < max)
    {
        new[i] = '\0';
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