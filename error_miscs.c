/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_miscs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:31:29 by recherra          #+#    #+#             */
/*   Updated: 2025/03/24 16:02:01 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
}

static void	print_error(char *error_msg)
{
	ft_putstr(error_msg);
	exit(1);
}

void	init_error(void *ptr)
{
	if (!ptr)
	{
		print_error("Unknown error happened!");
		exit(1);
	}
}
