/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cf_parsing__.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krid <ael-krid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:19:20 by ael-krid          #+#    #+#             */
/*   Updated: 2025/03/27 18:19:29 by ael-krid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	get_index(char *s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i] && s[i] != ',')
		i++;
	j = i;
	while (j != 0)
	{
		if (s[j] >= '0' && s[j] <= '9')
			break ;
		j--;
	}
	if (j == 0)
		return (-1);
	if (s[i] == ',')
	{
		j = i + 1;
		while (s[j] && s[j] == ' ')
			j++;
		if (s[j] == 0)
			return (-11);
	}
	return (i);
}

void	set_fr_fg_fb__(t_cu *cu, int x, char *s, int to_set)
{
	if (to_set)
	{
		if (x)
			cu->fr = ft_atoi(s);
		else
			cu->cr = ft_atoi(s);
		return ;
	}
	if (x)
		cu->fg = ft_atoi(s);
	else
		cu->cg = ft_atoi(s);
}

int	set_fr_fg_fb(t_cu *cu, char *s, int x)
{
	int	i;

	i = 0;
	i = get_index(s);
	if (i < 0)
		return (0);
	s[i] = '\0';
	set_fr_fg_fb__(cu, x, s, 1);
	s = s + i + 1;
	i = get_index(s);
	if (i < 0)
		return (0);
	s[i] = 0;
	set_fr_fg_fb__(cu, x, s, 0);
	s = s + i + 1;
	if (i < 0)
		return (0);
	if (x)
		cu->fb = ft_atoi(s);
	else
		cu->cb = ft_atoi(s);
	return (1);
}
