/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_dup_rooms.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:28:00 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/14 14:57:13 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

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

void	delete_link(t_room *room)
{
	t_link	*prev;
	t_link	*link;
	t_link	*tmp;

	link = room->link;
	tmp = NULL;
	if (link->room->name == room->name)
	{
		tmp = room->link;
		room->link = room->link->next;
	}
	else
		while (link)
		{
			prev = link;
			if (link->next->room->name == room->name)
			{
				tmp = link->next;
				prev->next = tmp->next;
				break ;
			}
			link = link->next;
		}
	free(tmp);
	tmp = NULL;
}

void	delete_links(t_room *room)
{
	t_link	*link;

	delete_link(room);
	delete_link(room->outroom);
	link = room->link;
	while (link && link->next)
		link = link->next;
	link->next = room->outroom->link;
	relink_to_inroom(room);
	change_prev_rooms(room);
	if (room->prev->name == room->name)
		room->prev = room->outroom->prev;
	free(room->outroom);
	room->outroom = NULL;
}

int		delete_dup_rooms(t_path *path)
{
	t_queue	*list;
	t_queue	*tmp;
	int		i;

	i = 0;
	while (i < path->size)
	{
		list = path[i++].list;
		while (list)
		{
			if (list->room->dup)
			{
				delete_links(list->room);
				list->room->dup = 0;
				list->room->in = 0;
				tmp = list->next;
				list->next = tmp->next;
				if (list->next)
					list->next->prev = list;
				free(tmp);
			}
			list = list->next;
		}
	}
	return (0);
}
