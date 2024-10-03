 #include "cubed.h"
size_t	ft_strlen(char *s)
{
	int	i;
	i = 0;
	while (s[i])
	    i++;
	return (i);
}
static void	join_the_two_strings(char *all, char const *s1, char const *s2)
{
	size_t	i;
	int		j;

	i = 0;
	if (s1 != 0)
	{
		while (s1[i])
		{
			all[i] = s1[i];
			i++;
		}
	}
	j = 0;
	while (s2[j])
	{
		all[i] = s2[j];
		i++;
		j++;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*allocated;
	size_t	string_len;
	size_t	x;

	x = 0;
	if (s1 != NULL)
	    x = ft_strlen(s1);
	string_len = x + ft_strlen(s2);
	allocated = (char *)malloc(string_len + 1);
	if (!allocated)
	{
		return (NULL);
	}
	join_the_two_strings(allocated, s1, s2);
	allocated[string_len] = '\0';
	free(s1);
	return (allocated);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*all;
    int i;
	size_t	tmp;

	i = 0;
	tmp = count * size;
	all = (char *)malloc(count * size);
	if (!all)
		return (NULL);
    while (i < count)
    {
        all[i] = 0;
        i++;
    }
	return (all);
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
    if (!next_line)
        return (NULL);
    int te;
    
    while (rt)
    {
        line = (char *) ft_calloc(len+1 , sizeof(char));
        rt = read(fd, line, len);
        if (rt == -1)
            exit(1);
        if (rt == 0 && ft_strlen(next_line) ==  0)
            {
                return (NULL);
            }
        if (rt == 0 || (len == 1 && *line == '\n'))
        {   
            free(line);
            break;
        }
        next_line = ft_strjoin(next_line, line);
        i++;
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

char  **news_textures(int fd, int len )
{
    char *str;
    char **news;
    int i;
    int x;
    char nb[5];

    i = 0;
    x = 0;
    news = (char **) malloc(sizeof(char *) *5);
    if (!news)
        return (NULL);
    news[4] = NULL; 
    while (1)
    {
        str = next_line(fd, 1);

        if (!str)
            {
                break;
            }
        i = 0;
        while (str[i] && str[i] == ' ')
            i++
            ;
        if (ft_strlen(str) < 3)
            continue;
        if (str[0] == 'N')
        {
            if (str[1] != 'O')
                return (NULL);
            if (str[2] != ' ' || nb[0] == '1')   
                return (NULL); // error!!!
            news[0] = strdup(str);
            nb[0] = '1';
        }
        else if (str[0] == 'E')
        {
            if (str[1] != 'A')
                return (NULL);
            if (str[2] != ' ' || nb[1] == '1')
                return (NULL);
            news[1] = strdup(str);
            nb[1] = '1';
        }
        else if (str[0] == 'W')
        {
            if (str[1] != 'E')
                return (NULL);
            if (str[2] != ' ' || nb[2] == '1')
                return (NULL);
            news[2] = strdup(str);
            nb[2] = '1';
        }
       else if (str[0] == 'S')
       {
            if (str[1] != 'O')
                return (NULL);
            if (str[2] != ' ' || nb[3] == '1')
                return (NULL);
            news[3] = strdup(str);
            nb[3] = '1';
        }
        else if (str[0] == '1' && str[1] == '1')
            {
                if (str[i+2] != '1')
                    {
                        return (NULL);
                    }
                break;
            }
        // else
        //     return (NULL);

        i++;
    }
    i = 0;
    while (i < 4)
    {
        if (nb[i] != '1')
            {
                return (NULL);
            }
        i++;
    }
    return (news);
}
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
        cu->fr = atoi(s);
    else
        cu->cr = atoi(s);
    s = s+i+1;
    i = get_index(s);
    s[i] = 0;
    if (x)
        cu->fb = atoi(s);// atoi error?
    else
        cu->cb = atoi(s);
    s = s+i+1;
    if (x)
        cu->fg = atoi(s);
    else
        cu->cg = atoi(s);
    return (1);
}

int set_fc(int fd, t_cu *cu)
{
    int f;
    int c;
    int i;

    i = 0;
    char *str;

    while (1)
    {
        str = next_line(fd, 1);
        if (!str )
            break;
        i = 0;
        while (str[i] && str[i] == ' ')
            i++
            ;
        if (str[i] == 'F')
        {
            if (str[1] != ' ' || str[2] == 0 || !len_(str+2) || f == 1)
                return (0);
            set_fr_fg_fb(cu, str+i+2, 1);
            f = 1;
        }
        else if (str[i] == 'C')
        {
            if (str[1] != ' ' || str[2] == 0 || !len_(str+2) || c == 1)
                return (0);
            set_fr_fg_fb(cu, str+2, 0);
            c = 1;
        }
        else if (str[0] == '1' && str[1] == '1')
            {
                if (str[i+2] != '1')
                    {
                        return (0);
                    }
                break;
            }
        // else
        //     return (0);
    }
    return (1);
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

int line_checks(char *s)
{
    int i;
    int x;
    int j;
    

    j = 0;
    i = 0;
    x = 0;

    while (s[i])
    {
        if (s[i] != ' ' && s[i] != '\n' && s[i] != '1' && s[i] != '0')// and != isspace()
            {
                if (!player_char(s[i], s, i))
                    return (0);
            }
        i++;
    }
    
    return (1);
}
    
    // if (!x)
    //     return (0);
    // s = s+j;
    // if (*s == '1')
    //     return (37);
    // if (*s == ' ')
    //     {
    //         i = 0;
    //         while (s[i] == ' ')
    //             i++
    //             ;
    //         if (s[i] == '1')
    //             return (13);
    //     }
    // return (0);

// }

size_t count_len(char *s)
{
    int count;

    count  = 0;
    while (*(s++))
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

char **alloc_map(char *str)
{
    int     i;
    int     j;
    int     cnt;
    char    **map;

    
    i = 0;
    while (str[i] && (str[i] == ' ' || str[i] == '\n'))
        i++
        ;
    if (!str[i] || str[i] != '1')
        return (NULL);
    cnt  = count_len(str);
    if (cnt < 3 || cnt == -1)
        return (NULL);
    map = (char **) malloc(sizeof(char *) * cnt+1);
    map[cnt] = NULL;
    if (!map)
        return (NULL);
    while (str[i])
    {

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

        if (str[i] == '1' && str[i+1] == '1')
            {
                if (str[i+2] != '1')
                    return (NULL);
                if (!line_checks(str+i))
                    return (NULL);
                
                // exit(1);
                // map = alloc_map(str);
                // if (!map)
                //     return (NULL);
                
            }
        i++;
    }
    
    // while (len--)
    // {
    //     if (str[len] == '\n' && str[len+1] != 0)// also check if the map is empty!
    //     {
    //         str = str+len+1;
    //         if (!line_checks(str))
    //             {
    //                 len--;
    //                 continue;
    //             }
    //         i = 0;
    //         map = alloc_map(str);
    //         if (!map)
    //             return (NULL);
    //         break;
    //     }
    // }
    return (map);
}

char **get_map(int fd)
{

    char **map;
    char *str;

    
    str = next_line(fd, 51);

    map = get_map__(str);
    if (!map)
        return (NULL);// exit / error.
    
    return (map);
}
int main(int argc , char **argv)
{
    char **str;
    char *s;
    t_cu *cu;
    int fd,f;
    
    cu = (t_cu *) malloc(sizeof(t_cu));
    fd = open("./x.cube", O_RDWR);
    if (!fd)
        return (0);
    // exit(1);
    cu->news = news_textures(fd , 1);
    if (!cu->news)
        {
            printf("?error\n");
            return (0);
        }
    close(fd);
    f = open("./x.cube", O_RDWR);
    if (!set_fc(f, cu))
        {
            printf("!!error\n");
            return (0);
        }
    printf("\t()()()()()()()\n");
    close(f);
    fd = open("./x.cube", O_RDWR);
    cu->map = get_map(fd);
    int i = 0;
    while (i < 3)
    {
        printf("%d\n", cu->fr);
        printf("%d\n", cu->fb);
        printf("%d\n", cu->fg);
        printf("-----\n%d\n", cu->cr);
        printf("%d\n", cu->cb);
        printf("%d\n", cu->cg);
        i++;
    }

}
