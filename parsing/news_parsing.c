/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   news_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krid <ael-krid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:21:20 by ael-krid          #+#    #+#             */
/*   Updated: 2025/03/27 18:21:22 by ael-krid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	set_news__(char *str, char c, int index_num, t_parsed_data *data_set,
		char **news)
{
	int	i;

	(void)c;
	i = data_set->i + 2;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == 0 || str[i] == '\n')
		return (0);
	if (str[data_set->i + 2] != ' ' || data_set->nb[index_num] == '1')
		return (0);
	news[index_num] = ft_strdup(str + data_set->i);
	data_set->nb[index_num] = '1';
	return (1);
}

int	parse_fc(t_parsed_data *data_set, char *str, t_cu *cu)
{
	if (str[data_set->i] == 'F')
	{
		if (!set_fc__(data_set, str, cu, 'F'))
		{
			return (0);
		}
	}
	else if (str[data_set->i] == 'C')
	{
		if (!set_fc__(data_set, str, cu, 'C'))
			return (0);
	}
	return (1);
}

int	parse_news(t_parsed_data *data_set, char **news, char *str)
{
	int	f;

	f = 0;
	if (str[data_set->i] == 'N')
	{
		if (str[data_set->i + 1] != 'O' || !set_news__(str, 'N', 0, data_set,
				news))
			return (0);
	}
	else if (str[data_set->i] == 'E')
	{
		if (str[data_set->i + 1] != 'A' || !set_news__(str, 'E', 1, data_set,
				news))
			return (0);
	}
	else if (str[data_set->i] == 'W')
	{
		if (str[data_set->i + 1] != 'E' || !set_news__(str, 'W', 2, data_set,
				news))
			return (0);
	}
	else if (str[data_set->i] == 'S')
	{
		if (!set_news__(str, 'S', 3, data_set, news))
			return (0);
	}
	return (1);
}

void	free_news(t_parsed_data *data_set, char **n)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data_set->nb[i] == '1')
			free(n[i]);
		i++;
	}
	free(n);
}

char	**set_parsed_data(t_parsed_data *data_set, int *map_check_ret)
{
	char **news;

	news = (char **)malloc(sizeof(char *) * 5);
	if (!news)
		return (NULL);
	news[0] = NULL;
	news[1] = NULL;
	news[2] = NULL;
	news[3] = NULL;
	news[4] = NULL;
	data_set->i = 0;
	data_set->c = 0;
	data_set->f = 0;
	*map_check_ret = 0;
	return (news);
}
