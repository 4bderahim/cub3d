/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 21:07:40 by recherra          #+#    #+#             */
/*   Updated: 2025/03/19 17:32:46 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	init_rays(t_all_data *data)
{
	data->rays = malloc(sizeof(t_ray) * N_RAYS);
	if (!data->rays)
		exit(1);
}
