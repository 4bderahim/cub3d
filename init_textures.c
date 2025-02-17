/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:51:05 by recherra          #+#    #+#             */
/*   Updated: 2025/02/17 15:33:47 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	fill_texture(int i, t_all_data *data, char **res)
{
	data->news[i]->path = ft_strdup(res[1]);
	data->news[i]->img = mlx_xpm_file_to_image(data->mlx.connection,
			data->news[i]->path, &data->news[i]->width, &data->news[i]->height);
	if (!data->news[i]->img)
		exit(1);
	data->news[i]->data.addr = mlx_get_data_addr(data->news[i]->img,
			&data->news[i]->data.bits_per_pixel,
			&data->news[i]->data.line_length, &data->news[i]->data.endian);
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
		if (!res)
			exit(1);
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
