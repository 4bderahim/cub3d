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

char	**free_str_null(char *str, t_cu *cu, char **map)
{
	if (cu == NULL)
		free(str);
	else
	{
		cu->map = map;
		free___(cu, 13);
		free(cu->map);
	}
	return (NULL);
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
		return (free_str_null(str, NULL, NULL));
	str[i + 1] = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '1')
		{
			map = alloc_map(str);
			if (!map)
				return (free_str_null(str, NULL, NULL));
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
				return (free_str_null(NULL, cu, map));
			j++;
		}
		i++;
	}
	return (map);
}
