#include "cubed.h"

void free___(t_cu *map, int st)
{
    int i;
    i = 0;
    if (!st)
    {
        write(2, "error\n[-] UNKNOWN ERROR ACCURED!\n", 33);
        return ;
    }
    if (st == 1)
        free(map);
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
char *next_line(int fd, int len )
{
    int i;
    int rt;
    char *line;
    char *next_line;
    i = 0;
    rt = 1;
    next_line = (char *) malloc(1);
    if (!next_line)
        return (NULL);
    next_line[0] = 0;
    int te;
    
    while (rt)
    {
        line = (char *) ft_calloc(len+1 , sizeof(char));
        rt = read(fd, line, len);
        if (rt == -1)
            exit(1);
        if (rt == 0 && ft_strlen(next_line) ==  0)
            return (NULL);
        if (rt == 0 || (len == 1 && *line == '\n'))
        {   
            free(line);
            break;
        }
        next_line = ft_strjoin(next_line, line);
        i++;
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

// char  **news_textures(int fd, int len )
// {
//     char *str;
//     int i;
//     int x;

//     i = 0;
//     x = 0;
//     char **news;
//     char nb[5];
//     news = (char **) malloc(sizeof(char *) *5);
//     if (!news)
//         return (NULL);
//     news[4] = NULL; 
//     while (1)
//     {
//         str = next_line(fd, 1);

//         if (!str)
//             {
//                 break;
//             }
//         i = 0;
//         while (str[i] && str[i] == ' ')
//             i++
//             ;
//         if (ft_strlen(str) < 3)
//             continue;
//         else if (str[0] == 'N')
//         {
//             if (str[1] != 'O')
//                 return (NULL);
//             if (str[2] != ' ' || nb[0] == '1')   
//                 return (NULL); // error!!!
//             news[0] = strdup(str);
//             nb[0] = '1';
//         }
//         else if (str[0] == 'E')
//         {
//             if (str[1] != 'A')
//                 return (NULL);
//             if (str[2] != ' ' || nb[1] == '1')
//                 return (NULL);
//             news[1] = strdup(str);
//             nb[1] = '1';
//         }
//         else if (str[0] == 'W')
//         {
//             if (str[1] != 'E')
//                 return (NULL);
//             if (str[2] != ' ' || nb[2] == '1')
//                 return (NULL);
//             news[2] = strdup(str);
//             nb[2] = '1';
//         }
//        else if (str[0] == 'S')
//        {
//             if (str[1] != 'O')
//                 return (NULL);
//             if (str[2] != ' ' || nb[3] == '1')
//                 return (NULL);
//             news[3] = strdup(str);
//             nb[3] = '1';
//         }
//         else if (str[0] == '1' && str[1] == '1')
//             {
//                 if (str[i+2] != '1')
//                     {
//                         return (NULL);
//                     }
//                 break;
//             }
//         // else
//         //     return (NULL);

//         i++;
//     }
//     i = 0;
//     while (i < 4)
//     {
//         if (nb[i] != '1')
//             {
//                 return (NULL);
//             }
//         i++;
//     }
//     return (news);
// }
int len_(char *s)
{
    int i;
    int j;

    j = 0;
    i = 0;
    while (s[i])
    {
        if (s[i] == ',' && s[i+1] != 0)
            j++;
        if(s[i] == ',' && (i == 0 || s[i+1] == ','))
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
        i++
        ;
    return (i);
}

int set_fr_fg_fb(t_cu *cu, char *s, int x)
{
    int i;
    i = 0;

    i = get_index(s);
    s[i] = '\0';
    if (x)
        cu->fr = ft_atoi(s);
    else
        cu->cr = ft_atoi(s);
    s = s+i+1;
    i = get_index(s);
    s[i] = 0;
    if (x)
        cu->fg = ft_atoi(s);
    else
        cu->cg = ft_atoi(s);
    s = s+i+1;
    if (x)
        cu->fb = ft_atoi(s);
    else
        cu->cb = ft_atoi(s);
    return (1);
}

int check_if_entries_filled(int f,int c , char nb[5], char *str_not_free)
{
    int i;
    if (!f || !c)
        return (0);
    i = 0;
    while (i < 4)
    {
        if (nb[i] != '1')
            return (0);
        i++;
    }
    free(str_not_free);
    return (1);
}

int set_map_direction(char direction, int location,char *str, char **news, t_map_pars *pars)
{
    if (str[pars->i+1] != direction)
        return (0);
    if (str[pars->i+2] != ' ' || pars->nb[location] == '1')   
        return (0); 
    news[location] = ft_strdup(str+pars->i);
    pars->nb[location] = '1';
    return (1);
}
char  **set_fc(int fd, t_cu *cu)
{
    t_map_pars pars;
    
    char **news;
    news = (char **) malloc(sizeof(char *) *5);
    if (!news)
        return (NULL);
    news[4] = NULL; 

    pars.i = 0;
    char *str;
    pars.c = 0;
    pars.f = 0;
    while (1)
    {
        str = next_line(fd, 1);
        if (!str )
            {
                break;
            }
        pars.i = 0;
        while (str[pars.i] && str[pars.i] == ' ')
            pars.i++
            ;
        if (str[pars.i] == 'F')
        {
            if (str[pars.i+1] != ' ' || str[pars.i+2] == 0 || !len_(str+2) || pars.f == 1)
                return (NULL);
            set_fr_fg_fb(cu, str+pars.i+2, 1);
            pars.f = 1;
        }
        else if (str[pars.i] == 'C')
        {
            if (str[pars.i+1] != ' ' || str[pars.i+2] == 0 || !len_(str+pars.i+2) || pars.c == 1)
                return (NULL);
            pars.c =  set_fr_fg_fb(cu, str+pars.i+2, 0);
        }
        else if (str[pars.i] == 'N')
        {
            if (!set_map_direction('O', 0, str, news,  &pars))
                return (NULL);
        }
        else if (str[pars.i] == 'E')
        {
            if (!set_map_direction('A', 1, str, news,  &pars))
                return (NULL);
            // if (str[pars.i+1] != 'A')
            //     return (NULL);
            // if (str[pars.i+2] != ' ' || pars.nb[1] == '1')
            //     return (NULL);
            // news[1] = strdup(str+pars.i);
            // pars.nb[1] = '1';
        }
        else if (str[pars.i] == 'W')
        {
            if (!set_map_direction('E', 2, str, news,  &pars))
                return (NULL);
           
        }
       else if (str[pars.i] == 'S')
       {
            if (!set_map_direction('O', 3, str, news,  &pars))
                return (NULL);
            
        }
        else if (str[pars.i] == '1')
            break;
        else
            {
                if (*(str+pars.i) != '\0')
                    return (NULL);
            }
        free(str);
    }
    if (!check_if_entries_filled(pars.f, pars.c, pars.nb, str))
        return (NULL);
    return (news);
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
            if ((s[i-1] != '1' && s[i-1] != '0' ) || (s[i+1] != '1' && s[i+1] != '0'))
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

    count  = 0;
    while (*(s))
    {
        if (*s == '\n')
            {
                if (*(s+1) == '\n')
                    return (-1);
                count++;
            }
        s++;
    }
    return (count+1);
}

char *fill_( char *s, int index,int map_index)
{
    int i;
    char *new;

    new = (char *) malloc(sizeof(char ) * (index+1));
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
char **alloc_map(char *str)
{
    int     i;
    int     j;
    int     cnt;
    char    **map;
    int     x;
    
    i = 0;
    x = 0;
    while (str[i])
    {
        if (str[i] == '1' && map_beg(str, i-1))
            {
                while(str[i] != '\n')
                    i--
                    ;
                i++;
                break;
            }
        i++;
    }
    str = str+i;
    cnt = count_len(str);
    if (cnt == -1)
        return (NULL);
    map = (char **) malloc(sizeof(char *) * (cnt+1));
    map[cnt] = NULL;
    if (!map)
        return (NULL);
    j = 0;
    i = 0;
    while (str[i])
    {
        x = 0;
        if (str[i] == '\n' || str[i+1] == 0)
            {
                map[j] = fill_( str, i, j);
                if (str[i+1] == 0)
                    break;
                j++;
                str = str+i+1;
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

    i = ft_strlen(str)-1;
    while (i >= 0 && (str[i] == ' ' || str[i] == '\n'))
        i--
        ;
    if (str[i-1] != '1')
        return (NULL);
    str[i+1] = 0;
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
        {
            free(str);
            free___(NULL, 0);
            exit(1);
        }
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
                if (!map[i][j+1] || map[i][j+1] == ' ' || j == 0 || map[i][j-1] ==  ' ')
                    return (0);
                if (j >= ft_strlen(map[i+1]) ||  map[i+1][j] == ' ')
                    return (0);
                if (j >= ft_strlen(map[i-1]) ||  map[i-1][j] == ' ')
                    return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

int not_walled(char **map)
{
    int i;
    int j;
    int map_len;
    int line_len;
    i = 0;
    map_len = 0;
    while (map[map_len])
        map_len++
        ;
    while (map[i])
    {   
        j = 0;
        while (map[i][j] == ' ')
            j++
            ;
        if (!map[i][j])
            {
                i++;
                continue;
            }
        if (map[i][j] != '1' && map[i][j] != ' ')
            return (1);
        line_len = ft_strlen(map[i])-1;
        while (map[i][line_len] == ' ')
            line_len--
            ;
        if (map[i][line_len] != '1' )
            return (1);
        j = 0;
        if (i == 0 || i == map_len-1)
        {
            while (map[i][j])
            {
                if (map[i][j] != '1' && map[i][j] != ' ')
                    return (1);
                j++;
             }
        }
        i++;
    }
    if (!check_map(map))
        {
            //free all
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
        j= 0 ;
        while (map[i][j])
        {
            if ((map[i][j] == 'N' ||map[i][j] == 'E' || map[i][j] == 'W' ||map[i][j] == 'S'))
            {
                if (x)
                    return (0);
                x= 1;
            }
            j++;
        }
        i++;
    }
    return (1);
}


t_cu *fetch__()
{
    char **str;
    char *s;
    t_cu *cu;
    int fd,f;
    
    cu = (t_cu *) malloc(sizeof(t_cu));
    fd = open("./x.cube", O_RDWR);
    if (!fd)
        return (0);
    f = open("./x.cube", O_RDWR);
    cu->news = set_fc(f, cu);
    if (!(cu->news))
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
        printf("[%s]\n", cu->map[i]);
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