#include "../cubed.h"

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

int alloc_next_line(char **next_line)
{
    *next_line = (char *)malloc(1);
    if (!next_line)
        return (0);
    (*next_line)[0] = 0;
    return (1);
}
void free_line_and_tmp(char *tmp, char *line)
{
    free(tmp);
    free(line);
}

char *next_line(int fd, int len)
{
    int rt;
    char *line = NULL;
    char *next_line;
    char *tmp;
    char *line_tmp;

    next_line = NULL;
    rt = alloc_next_line(&next_line);
    while (rt)
    {
        line_tmp = line;
        line = (char *)ft_calloc(len + 1, sizeof(char));
        free(line_tmp);
        rt = read(fd, line, len);
        if (rt == -1)
            exit(1);
        if (rt == 0 && ft_strlen(next_line) == 0)
            return (NULL);
        if (rt == 0 || (len == 1 && *line == '\n'))
        {
            free(line);
            break;
        }
        tmp = next_line;
        next_line = ft_strjoin(next_line, line);
        free(tmp);
    }
    //  more checkss//
    return (next_line);
}
