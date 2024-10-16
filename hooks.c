/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:51:18 by recherra          #+#    #+#             */
/*   Updated: 2024/10/10 20:51:20 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void up_down(t_all_data *data, int direction)
{
    t_direction _direction;
    set_direction(&_direction, data->player.player_angle_rad);



    float factor_x = cos(data->player.player_angle_rad) * 3 ;
    float factor_y = sin(data->player.player_angle_rad) * 3 ;

    data->player.x += factor_x * direction;
    data->player.y += factor_y * direction;

    // int  position_x = (_direction.right && direction == -1) ?  (data->player.x + 2) / data->minimap.tile : (data->player.x - 2) / data->minimap.tile ;
    // int  position_y = (_direction.up && direction == -1) ? (data->player.y - 2) / data->minimap.tile : (data->player.y + 2)  / data->minimap.tile;
    
    // if (data->cu_map->map[position_y][position_x] == '1')
    // {
    //         data->player.x -= factor_x * direction;
    //         data->player.y -= factor_y * direction;
    //         return ;
    // }
    data->endpoint.x += factor_x * direction;
    data->endpoint.y += factor_y * direction;
}

static void    right_left(t_all_data *data, int direction)
{
    t_direction _direction;
    set_direction(&_direction, data->player.player_angle_rad);


    float degree = data->player.player_angle_rad - (90 * to_rad);
    float cos_ = cos(degree) * 3 ;
    float sin_ = sin(degree) * 3 ;
    data->player.x += cos_ * direction;
    data->player.y += sin_ * direction;

    
    // int  position_x = (_direction.up && direction == 1) ?  (data->player.x + 2) / data->minimap.tile : (data->player.x - 2) / data->minimap.tile ;
    // int  position_y = (_direction.right && direction == 1) ? (data->player.y + 2) / data->minimap.tile : (data->player.y - 2)  / data->minimap.tile;

    // // int position_x = (data->player.x + 1) / data->minimap.tile;
    // // int position_y = (data->player.y + 1)  / data->minimap.tile;
    
    
    // if (data->cu_map->map[position_y][position_x] == '1')
    //     {
    //         data->player.x -= cos_ * direction;
    //         data->player.y -= sin_ * direction;
    //         return ;
    //     }
    data->endpoint.x += cos_ * direction;
    data->endpoint.y += sin_ * direction;
}

void re_position_player(int keycode, t_all_data *data)
{
    if (keycode == WK)
        up_down(data, -1);
    else if (keycode == SK)
        up_down(data, 1);
    else if (keycode == AK)
        right_left(data, -1);
    else if (keycode == DK)
        right_left(data, 1);
}

void    re_pov(int keycode, t_all_data *data)
{
    if (keycode == RA)
        rotate(data, 1);
    else if (keycode == LA)
        rotate(data, -1);
}
