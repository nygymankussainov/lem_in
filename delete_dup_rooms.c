/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_dup_rooms.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:28:00 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/24 17:03:58 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	relink_to_inroom(t_room *room)
{
	t_link	*relink;
	t_link	*link;

	link = room->link;
	while (link)
	{
		relink = link->room->link;
		while (relink)
		{
			if (relink->room->name == room->name &&
				relink->room != room)
				relink->room = room;
			relink = relink->next;
		}
		link = link->next;
	}
}

void	delete_links(t_room *room)
{
	t_link	*link;
	t_link	*tmp;

	link = room->link;
	while (link && link->next)
		link = link->next;
	link->next = room->outroom->link;
	link = room->link;
	if (link->room->name == room->name)
	{
		tmp = link->next;
		free(link);
		link = NULL;
		link = tmp;
		room->link = link;
	}
	while (link)
	{
		if (link && link->next && link->next->room->name == room->name)
		{
			tmp = link->next;
			link->next = tmp->next;
			free(tmp);
			tmp = NULL;
		}
		link = link->next;
	}
	relink_to_inroom(room);
	change_prev_rooms(room);
}

void	delete_dup_rooms(t_path *path)
{
	t_queue	*list;
	int		i;

	i = 0;
	while (i < path->size)
	{
		list = path[i].list;
		while (list)
		{
			if (list->room->dup)
			{
				delete_links(list->room);
				free(list->room->outroom);
				list->room->outroom = NULL;
				list->room->dup = 0;
				list->room->in = 0;
			}
			list = list->next;
		}
		i++;
	}
}
