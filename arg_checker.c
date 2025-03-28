/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:18:04 by recherra          #+#    #+#             */
/*   Updated: 2025/03/28 17:18:36 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	arg_checker(int ac, char *map)
{
	int len;

	if (ac != 2)
		print_error("Error\nToo many/few arguments!");
	len = ft_strlen(map);
	if (!ft_strnstr(map + (len - 4), ".cub", 4))
		print_error("Error\nInvalid file!");
}