/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_links.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 11:31:58 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/09 18:13:45 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lem_in.h"

int		count_dash(char *line)
{
	int		i;

	i = 0;
	while (*line)
	{
		if (*line == '-')
			i++;
		line++;
	}
	if (i != 1)
		return (0);
	return (1);
}

int		validate_links(t_hash_tab *h_tab, t_farm *farm)
{
	ft_strdel(&farm->line);
	while (get_next_line(farm->fd, &farm->line) == 1)
	{
		if (count_dash(farm->line) && islink(farm->line))
		{
			if (!find_and_connect_rooms(farm->line, h_tab, farm->size))
				return (0);
		}
		else if (farm->line[0] == '#' &&
			ft_strcmp("##start", farm->line) && ft_strcmp("##end", farm->line))
		{
			ft_strdel(&farm->line);
			continue ;
		}
		else if (count_space(farm->line))
		{
			ft_strdel(&farm->line);
			while (get_next_line(farm->fd, &farm->line) == 1)
				ft_strdel(&farm->line);
		}
		else
			return (0);
		ft_strdel(&farm->line);
	}
	return (1);
}
