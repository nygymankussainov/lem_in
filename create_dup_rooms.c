/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_dup_rooms.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 15:32:36 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/28 12:57:24 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
			new->next->prev = new;
			new->prev = list;
			list->next = new;
		}
		list = list->next;
	}
}

void	change_prev_rooms(t_room *room)
{
	t_link	*link;

	link = room->link;
	while (link)
	{
		if (link->room->name != room->name &&
			link->room->prev &&
			link->room->prev->name == room->name)
			link->room->prev = room;
		link = link->next;
	}
}

void	manage_links(t_queue *list, t_room *room)
{
	t_link	*right;
	t_link	*left;
	t_link	*link;
	t_link	*inroom;

	if (!(right = (t_link *)ft_memalloc(sizeof(t_link))) ||
		!(inroom = (t_link *)ft_memalloc(sizeof(t_link))))
		exit(0);
	inroom->room = room;
	right->room = room->outroom;
	// right->lock = 1;
	link = room->outroom->link;
	if (room->outroom->link->room == list->prev->room)
	{
		left = room->outroom->link;
		inroom->next = room->outroom->link->next;
		left->next = NULL;
		room->outroom->link = inroom;
	}
	else
	{
		while (room->outroom->link)
		{
			if (room->outroom->link->next->room == list->prev->room)
				break ;
			room->outroom->link = room->outroom->link->next;
		}
		left = room->outroom->link->next;
		room->outroom->link->next = inroom;
		room->outroom->link = link;
	}
	left->room = left->room->outroom ? left->room->outroom : left->room;
	right->next = left;
	room->link = right;
	change_prev_rooms(room->outroom);
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
	new->prev = room;
	new->next = room->next;
	new->link = room->link;
	room->link = NULL;
	room->outroom = new;
	room->dup = 1;
	room->in = 1;
	manage_links(list, room);
}

void	create_dup_rooms(t_path *path)
{
	int		i;
	t_queue	*list;
	t_link	*link;

	i = 0;
	while (i < path->size)
	{
		list = path[i].list;
		while (list)
		{
			if (!list->room->dup && !list->room->status)
				duplicate_room(list);
			else if (list->room->status == 'e')
			{
				link = list->room->link;
				while (link)
				{
					if (link->room == list->prev->room)
						link->room = link->room->outroom;
					link = link->next;
				}
			}
			list = list->next;
		}
		add_dup_rooms_in_list(path[i].list);
		i++;
	}
}
