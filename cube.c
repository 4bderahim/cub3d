/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:12:50 by recherra          #+#    #+#             */
/*   Updated: 2025/03/21 18:23:27 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int close_btn(t_all_data *data)
{
    mlx_destroy_image(data->mlx.connection, data->game_img.img);
    mlx_destroy_window(data->mlx.connection, data->mlx.window);
    exit(0);
}

int key_check(int key)
{
    if (key == WK || key == AK || key == SK || key == DK || key == RA || key == LA)
        return (1);
    return (0);
}


int mouse_hook(int x, int y, t_all_data *data)
{
    (void)y;
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        rebuild(data);
        if (x < data->prev_x)
            rotate(data, -1, true);
        else if (x > data->prev_x)
            rotate(data, 1, true);
        data->prev_x = x;
        free(data->rays);
        data->rays = NULL;
        init_rays(data);
        cast_rays(data);
        game(data);
        mini_map(data, data->cu_map);
        put_images_to_window(data);
    }
    return (0);
}

void    set_state(t_all_data *data, int keycode, int state)
{
    if (keycode == WK)
        data->state.w = state;
    if (keycode == SK)
        data->state.s = state;
    if (keycode == AK)
        data->state.a = state;
    if (keycode == DK)
        data->state.d = state;
    if (keycode == RA)
        data->state.right_arrow = state;
    if (keycode == LA)
        data->state.left_arrow = state;
}

int key_press(int keycode, t_all_data *data)
{
    if (keycode == ESC)
    {
        mlx_destroy_window(data->mlx.connection, data->mlx.window);
        exit(0);
    }
    if (key_check(keycode) == 0)
        return 0;
    set_state(data, keycode, 1);
    return (0);
}

int key_release(int keycode, t_all_data *data)
{
    set_state(data, keycode, 0);
    return (0);
}

void initialize_keys_state(t_all_data *data)
{
    data->state.w = 0;
    data->state.a = 0;
    data->state.s = 0;
    data->state.d = 0;
    data->state.left_arrow = 0;
    data->state.right_arrow = 0;
    data->prev_x = 0;
}

int check_state(t_all_data *data)
{
    if (data->state.w || data->state.s || data->state.a || data->state.d || data->state.right_arrow || data->state.left_arrow)
        return 1;
    return 0;
}

void    re_render(t_all_data *data)
{
    rebuild(data);
    free(data->rays);
    data->rays = NULL;
    init_rays(data);
    cast_rays(data);
    game(data);
    mini_map(data, data->cu_map);
    put_images_to_window(data);      
}

int ultimate_hook(t_all_data *data)
{
    int check = 0;

    if (check_state(data))
        check = 1;
    if (data->state.w)
        up_down(data, -1);
    if (data->state.s)
        up_down(data, 1);
    if (data->state.a)
        right_left(data, -1);
    if (data->state.d)
        right_left(data, 1);
    if (data->state.right_arrow)
        rotate(data, 1, false);
    if (data->state.left_arrow)
        rotate(data, -1, false);
    if (check == 1)
        re_render(data);
    return 0;
}

int main(void)
{
    t_all_data data;

    data.cu_map = fetch__();
    if (!data.cu_map)
        return (0);
    initialize_keys_state(&data);
    height_width(data.cu_map);
    minimap_calcs(&data, data.cu_map);
    mlx_initial(&data.mlx, &data.game_img);
    init_textures(&data);
    player_position(&data, data.cu_map);
    initial_endpoint(&data);
    init_rays(&data);
    cast_rays(&data);
    game(&data);
    mini_map(&data, data.cu_map);
    put_images_to_window(&data);
    mlx_hook(data.mlx.window, 2, 1L << 0, key_press, &data);  
    mlx_hook(data.mlx.window, 3, 1L << 1, key_release, &data); 
    mlx_hook(data.mlx.window, 6, 1L << 6, mouse_hook, &data);
    mlx_loop_hook(data.mlx.connection, ultimate_hook,  &data);
    mlx_hook(data.mlx.window, 17, 0, close_btn, &data);
    mlx_loop(data.mlx.connection);
}
