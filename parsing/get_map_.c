/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krid <ael-krid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:20:19 by ael-krid          #+#    #+#             */
/*   Updated: 2025/03/27 18:20:21 by ael-krid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

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

int	check_empty_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			if (str[i + 1] == '\n')
				return (-1);
		}
		i++;
	}
	return (0);
}

int	set_map(char **map, char *str, int max_size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\n' || str[i + 1] == 0)
		{
			if (str[i + 1] == '\n')
				return (0);
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
	return (1);
}

char	**alloc_map(char *str)
{
	int		max_size;
	char	**map;

	map = NULL;
	str = str + get_i_index(map, str);
	if (check_empty_line(str) == -1)
		return (NULL);
	map = alloc_full_map(str);
	max_size = max_len(str);
	if (!set_map(map, str, max_size))
		return (NULL);
	return (map);
}
