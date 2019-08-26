/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_links.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 11:31:58 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/26 13:30:58 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

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

t_link	*create_slink(t_room *room, char *linkname)
{
	t_link	*new;
	t_link	*tmp;

	if (room->link)
	{
		tmp = room->link;
		while (tmp)
		{
			if (!ft_strcmp(linkname, tmp->name))
				return (room->link);
			tmp = tmp->next;
		}
		if (!(new = (t_link *)ft_memalloc(sizeof(t_link))))
			return (NULL);
		new->next = room->link;
		room->link = new;
	}
	else
	{
		if (!(room->link = (t_link *)ft_memalloc(sizeof(t_link))))
			return (NULL);
		room->link->next = NULL;
	}
	return (room->link);
}

int		validate_links(t_room **room, t_farm *farm, t_hashcodes *hashcodes)
{
	ft_strdel(&farm->line);
	while (get_next_line(farm->fd, &farm->line) == 1)
	{
		if (count_dash(farm->line) && islink(farm->line))
		{
			if (!find_and_connect_rooms(farm->line, room, hashcodes))
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
			return (1);
		}
		else
			return (0);
		ft_strdel(&farm->line);
	}
	return (1);
}
