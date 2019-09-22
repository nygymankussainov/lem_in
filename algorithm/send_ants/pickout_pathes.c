/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickout_pathes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:24:32 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/22 13:30:01 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path	*ft_path_init(t_farm *farm, t_room *room)
{
	t_path	*path;

	if (!(path = (t_path*)malloc(sizeof(t_path))) ||
	!(path->prev = (t_path*)malloc(sizeof(t_path))))
		exit(0);
	path->prev->prev = NULL;
	path->prev->room = farm->startroom;
	path->room = room;
	path->prev->next = path;
	return (path);
}

bool	ft_if_destroy(t_room *room1, t_room *room2)
{
	t_link	*link;

	link = room2->link;
	while (link)
	{
		if (!ft_strcmp(link->room->name, room1->name))
			break ;
		link = link->next;
	}
	if (link->lock == true || link->destroy == true)
		return (1);
	return (0);
}

t_link	*ft_get_next_link(t_room *room)
{
	t_link	*tmplink;

	tmplink = room->link;
	while (tmplink)
	{
		if (tmplink->lock == 1 && tmplink->destroy == 0)
			break ;
		tmplink = tmplink->next;
	}
	return (tmplink);
}

void	ft_visit(t_room *room)
{
	if (room->parent)
	{
		room->parent->out->visited = 1;
		room->parent->in->visited = 1;
	}
	else
		room->visited = 1;
}

t_path	*ft_get_path(t_farm *farm, t_room *room)
{
	t_path	*path;
	t_path	*tmppath;
	t_link	*link;

	path = ft_path_init(farm, room);
	ft_visit(room);
	while (room != farm->endroom)
	{
		link = ft_get_next_link(room);
		if (!(path->next = (t_path*)malloc(sizeof(t_path))))
			exit(0);
		// ft_visit(link->room);
		link->room->visited = true;
		tmppath = path;
		path->next->room = link->room;
		path = path->next;
		path->prev = tmppath;
		room = link->room;
	}
	path->next = NULL;
	return (path);
}

t_path	**ft_pickout_pathes(t_farm *farm, int pathcount)
{
	t_path	**pathes;
	t_link	*linkstart;
	int		pathnbr;

	if (!(pathes = (t_path**)malloc(sizeof(t_path*) * pathcount)))
		exit(0);
	linkstart = farm->startroom->link;
	pathnbr = 0;
	while (linkstart)
	{
		if (linkstart->lock)
		{
			pathes[pathnbr] = ft_get_path(farm, linkstart->room);
			pathnbr++;
		}
		linkstart = linkstart->next;
	}
	return (pathes);
}
