/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_dup_rooms.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 15:32:36 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/16 19:24:26 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	add_dup_rooms_in_list(t_queue *list)
{
	t_queue	*new;

	while (list)
	{
		if (list->room->dup && list->room->in)
		{
			if (!(new = (t_queue *)ft_memalloc(sizeof(t_queue))))
				exit(0);
			new->index = list->index;
			new->steps = list->steps;
			new->room = list->room->outroom;
			new->next = list->next;
			if (new->next)
				new->next->prev = new;
			new->prev = list;
			list->next = new;
		}
		list = list->next;
	}
}

void	manage_links(t_queue *list, t_room *room)
{
	t_link	*left;
	t_link	*right;
	t_link	*link;

	if (!(left = (t_link *)ft_memalloc(sizeof(t_link))) ||
		!(right = (t_link *)ft_memalloc(sizeof(t_link))))
		exit(0);
	link = room->outroom->link;
	while (link && link->room != list->prev->room)
		link = link->next;
	left->room = !list->prev->room->dup ?
		list->prev->room : list->prev->room->outroom;
	left->weight = -1;
	left->go = link->go;
	left->lock = link->lock;
	right->room = room->outroom;
	left->next = right;
	room->link = left;
	link->room = room;
	link->weight = 0;
	link->lock = 0;
}

void	duplicate_room(t_queue *list)
{
	t_room	*new;
	t_room	*room;

	room = list->room;
	if (!(new = (t_room *)ft_memalloc(sizeof(t_room))))
		exit(0);
	new->dup = 1;
	new->out = 1;
	new->name = room->name;
	new->dist = room->dist;
	new->inroom = room;
	new->next = room->next;
	new->link = room->link;
	room->link = NULL;
	room->prev = NULL;
	room->outroom = new;
	room->dup = 1;
	room->in = 1;
	manage_links(list, room);
}

void	create_dup_rooms(t_path *path)
{
	int		i;
	t_queue	*list;

	i = 0;
	while (i < path->size)
	{
		list = path[i].list;
		while (list)
		{
			if (!list->room->dup && !list->room->status)
				duplicate_room(list);
			else if (list->room->status == 'e')
				change_link_room(list);
			list = list->next;
		}
		add_dup_rooms_in_list(path[i].list);
		i++;
	}
}
