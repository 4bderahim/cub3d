/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map__.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:20:41 by ael-krid          #+#    #+#             */
/*   Updated: 2025/03/28 20:09:13 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	free_all(t_cu *map)
{
	int	i;

	i = 0;
	free(map->news[0]);
	free(map->news[1]);
	free(map->news[2]);
	free(map->news[3]);
	while (map->map[i])
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
	free(map->news);
	free___(map, 1);
	return (1);
}

int	map_last_checks(char **map)
{
	if (!check_map(map))
		return (1);
	return (0);
}

int	not_walled(char **map, t_cu *cu)
{
	int	i;
	int	j;
	int	map_len;

	(void)cu;
	map_len = 0;
	i = 0;
	while (map[map_len])
		map_len++;
	while (map[i])
	{
		j = 0;
		while (map[i][j] == ' ')
			j++;
		if (!map[i][j])
		{
			i++;
			continue ;
		}
		if (not_valid(i, j, map_len, map))
			return (1);
		i++;
	}
	return (map_last_checks(map));
}

int	correct_map(char **map)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	x = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'W'
					|| map[i][j] == 'S'))
			{
				if (x)
					return (0);
				x = 1;
			}
			j++;
		}
		i++;
	}
	if (!x)
		return (0);
	return (1);
}

void	check_not_walled_map(t_cu *cu)
{
	if (!cu->map)
	{
		free(cu->news[0]);
		free(cu->news[1]);
		free(cu->news[2]);
		free(cu->news[3]);
		free(cu->news);
		exit(1);
	}
	if (not_walled(cu->map, cu) || !correct_map(cu->map))
	{
		free_all(cu);
		exit(1);
	}
}
