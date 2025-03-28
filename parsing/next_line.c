/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krid <ael-krid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:21:32 by ael-krid          #+#    #+#             */
/*   Updated: 2025/03/27 18:21:34 by ael-krid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	free___(t_cu *map, int st)
{
	int	i;

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

int	alloc_next_line(char **next_line)
{
	*next_line = (char *)malloc(1);
	if (!next_line)
		return (0);
	(*next_line)[0] = 0;
	return (1);
}

char	*free_lines(char *line, char *next_line)
{
	free(next_line);
	free(line);
	return (NULL);
}

char	*next_line(int fd, int len)
{
	int		rt;
	char	*line;
	char	*next_line;

	line = NULL;
	next_line = NULL;
	rt = alloc_next_line(&next_line);
	while (rt)
	{
		line = (char *)ft_calloc(len + 1, sizeof(char));
		rt = read(fd, line, len);
		if (rt == -1)
			exit(1);
		if (rt == 0 && ft_strlen(next_line) == 0)
			return (free_lines(next_line, line));
		if (rt == 0 || (len == 1 && *line == '\n'))
		{
			free(line);
			break ;
		}
		next_line = ft_strjoin(next_line, line);
		free(line);
	}
	return (next_line);
}
