/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:51:05 by recherra          #+#    #+#             */
/*   Updated: 2025/03/27 18:23:42 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	err_and_exit(void)
{
	write(2, "error!", 6);
	exit(1);
}

static void	fill_texture(int i, t_all_data *data, char **res)
{
	data->news[i]->path = ft_strdup(res[1]);
	data->news[i]->img = mlx_xpm_file_to_image(data->mlx.connection,
			data->news[i]->path, &data->news[i]->width, &data->news[i]->height);
	if (!data->news[i]->img)
		err_and_exit();
	data->news[i]->data.addr = mlx_get_data_addr(data->news[i]->img,
			&data->news[i]->data.bits_per_pixel,
			&data->news[i]->data.line_length, &data->news[i]->data.endian);
}

static int	arr_len(char **res)
{
	int	i;

	i = 0;
	while (res[i])
		i++;
	return (i);
}

void	init_textures(t_all_data *data)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	data->news = malloc(sizeof(t_textures *) * 4);
	if (!data->news)
		exit(1);
	res = NULL;
	while (data->cu_map->news[i])
	{
		res = ft_split(data->cu_map->news[i], ' ');
		if (!res || arr_len(res) != 2)
			err_and_exit();
		data->news[i] = malloc(sizeof(t_textures));
		if (!data->news[i])
			exit(1);
		fill_texture(i, data, res);
		j = 0;
		while (res[j])
			free(res[j++]);
		free(res);
		i++;
	}
}
