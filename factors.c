/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:27:09 by recherra          #+#    #+#             */
/*   Updated: 2024/10/10 21:27:20 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void    re_calculate_factors(t_all_data *data)
{
    int i = 0;

    float dx = data->endpoint.x - data->player.x;
    float dy = data->endpoint.y - data->player.y;
    if (fabs(dx) >= fabs(dy))
        data->player.steps = fabs(dx);
    else
        data->player.steps = fabs(dy);
    data->player.factor_x = dx / data->player.steps;
    data->player.factor_y = dy / data->player.steps;
}
