/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickout_pathes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:24:32 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/18 14:36:00 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

bool	ft_if_destroy(t_room *room1, t_room *room2)
{
	t_link	*link;

	link = room2->link;
	while (link)
	{
		if (link->room == room1)
			break ;
		link = link->next;
	}
	if (link->lock == true)
		return (1);
	return (0);
}

t_link	*ft_get_next_link(t_room *room)
{
	t_link	*tmplink;

	if (room->induplicate)
		tmplink = room->parent->out->link;
	else
		tmplink = room->link;
	while (tmplink)
	{
		if (tmplink->lock == 1 && ft_if_destroy(room, tmplink->room) == 0)
			break ;
		tmplink = tmplink->next;
	}
	return (tmplink);
}

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

t_path	*ft_get_path(t_farm *farm, t_room *room)
{
	t_path	*path;
	t_path	*tmppath;
	t_link	*link;

	path = ft_path_init(farm, room);
	while (room != farm->endroom)
	{
		link = ft_get_next_link(room);	
		if (!(path->next = (t_path*)malloc(sizeof(t_path))))
			exit(0);
		link->room->visited = 1;
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
