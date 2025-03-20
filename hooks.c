/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:51:18 by recherra          #+#    #+#             */
/*   Updated: 2025/02/17 16:54:31 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void re_position_player(int keycode, t_all_data *data)
{
    if (keycode == WK)
        up_down(data, -1);
    if (keycode == SK)
        up_down(data, 1);
    if (keycode == AK)
        right_left(data, -1);
    if (keycode == DK)
        right_left(data, 1);
}

void re_pov(int keycode, t_all_data *data)
{
    if (keycode == RA)
        rotate(data, 1, false);
    if (keycode == LA)
        rotate(data, -1, false);
}
