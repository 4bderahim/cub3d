/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krid <ael-krid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:20:19 by ael-krid          #+#    #+#             */
/*   Updated: 2025/03/27 18:20:21 by ael-krid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cube.h"

int	get_i_index(char **map, char *str)
{
	int	i;

	(void)map;
	i = 0;
	while (str[i])
	{
		if (str[i] == '1' && map_beg(str, i - 1))
		{
			while (str[i] != '\n')
				i--;
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

char	**alloc_full_map(char *str)
{
	char	**map;
	int		cnt;

	map = NULL;
	cnt = count_len(str);
	if (cnt == -1)
		return (NULL);
	map = (char **)malloc(sizeof(char *) * (cnt + 1));
	map[cnt] = NULL;
	if (!map)
		return (NULL);
	return (map);
}

int	max_len(char *s)
{
	int	i;
	int	x;

	i = 0;
	x = -1;
	while (s[i])
	{
		if (s[i] == '\n' || s[i + 1] == '\0')
		{
			if ((x) < (i))
			{
				x = i;
			}
			s += i + 1;
			i = -1;
		}
		i++;
	}
	return (x + 1);
}
char	**alloc_map(char *str)
{
	int		i;
	int		j;
	char	**map;
	int		max_size;

	map = NULL;
	j = 0;
	i = 0;
	str = str + get_i_index(map, str);
	while (str[i])
	{
		if (str[i] == '\n')
		{
			if (str[i + 1] == '\n')
				return (NULL);
		}
		i++;
	}
	i = 0;
	map = alloc_full_map(str);
	max_size = max_len(str);
	while (str[i])
	{
		if (str[i] == '\n' || str[i + 1] == 0)
		{
			if (str[i + 1] == '\n')
				return (NULL);
			if (str[i + 1] == 0)
				map[j] = fill_(str, i + 1, max_size);
			else
				map[j] = fill_(str, i, max_size);
			if (str[i + 1] == 0)
				break ;
			j++;
			str = str + i + 1;
			i = -1;
		}
		i++;
	}
	return (map);
}

char	**get_map__(char *str)
{
	int		i;
	char	**map;

	map = NULL;
	i = ft_strlen(str) - 1;
	while (i >= 0 && (str[i] == ' ' || str[i] == '\n'))
		i--;
	if (str[i - 1] != '1')
	{
		free(str);
		return (NULL);
	}
	str[i + 1] = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '1')
		{
			map = alloc_map(str);
			if (!map)
			{
				free(str);
				return (NULL);
			}
			free(str);
			break ;
		}
		i++;
	}
	return (map);
}

char	**get_map(int fd, t_cu *cu)
{
	char	**map;
	char	*str;
	int		i;
	int		j;

	i = 0;
	str = next_line(fd, 51);
	map = get_map__(str);
	if (!map)
		return (NULL);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != ' ' && map[i][j] != '1'
				&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E'
				&& map[i][j] != 'W')
			{
				cu->map = map;
				free___(cu, 13);
				free(cu->map);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	return (map);
}
