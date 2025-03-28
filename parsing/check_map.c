/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krid <ael-krid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:20:01 by ael-krid          #+#    #+#             */
/*   Updated: 2025/03/27 18:20:03 by ael-krid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	not_valid(int i, int j, int map_len, char **map)
{
	int	line_len;

	line_len = 0;
	if (map[i][j] != '1' && map[i][j] != ' ')
		return (1);
	line_len = ft_strlen(map[i]) - 1;
	while (map[i][line_len] == ' ')
		line_len--;
	if (map[i][line_len] != '1')
		return (1);
	if (i == 0 || i == map_len - 1)
	{
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != ' ')
				return (1);
			j++;
		}
	}
	return (0);
}
