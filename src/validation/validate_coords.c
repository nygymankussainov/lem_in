/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_coords.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 13:14:26 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/14 12:18:56 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lem_in.h"

int		isduplicate(t_coords *coords)
{
	t_coords	*tmp;

	while (coords->next)
	{
		tmp = coords->next;
		while (tmp)
		{
			if (coords->x == tmp->x && coords->y == tmp->y)
				return (1);
			tmp = tmp->next;
		}
		coords = coords->next;
	}
	return (0);
}

int		count_space(char *line)
{
	int	sp;

	sp = 0;
	while (*line)
	{
		if (*line == ' ')
			sp++;
		line++;
	}
	if (sp != 2)
		return (0);
	return (1);
}

int		validate_coords(char *line)
{
	int		i;
	int		j;
	char	*x;

	if (!count_space(line))
		return (0);
	i = ft_strlen(line);
	while (i >= 0 && line[i] != ' ')
		i--;
	if (i < 0 || !isint(line + i + 1, 'r'))
		return (0);
	j = i;
	i--;
	while (i >= 0 && line[i] != ' ')
		i--;
	x = ft_strndup(line + i + 1, j - i - 1);
	if (!isint(x, 'r') || i - 1 < 0)
	{
		ft_strdel(&x);
		return (0);
	}
	ft_strdel(&x);
	return (i);
}
