/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_linkwith_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 21:57:00 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/21 16:57:25 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		link_back(t_room *room, t_queue *list)
{
	t_queue	*linkwith;

	linkwith = list;
	while (linkwith)
	{
		if (linkwith->room == room && list->room->status != 'e')
			return (1);
		linkwith = linkwith->next;
	}
	return (0);
}

void	linkwith_start(t_room *room1, t_room *room2)
{
	t_queue	*new;

	if (!(new = (t_queue *)ft_memalloc(sizeof(t_queue))))
		exit(0);
	if (room1->status == 's')
	{
		new->room = room2;
		new->next = room1->linkwith;
		room1->linkwith = new;
	}
}

void	delete_linkwith_rooms(t_queue *list)
{
	t_queue	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

void	create_linkwith_list(t_room *room1, t_room *room2)
{
	if (!room1->linkwith)
	{
		if (!(room1->linkwith = (t_queue *)ft_memalloc(sizeof(t_queue))))
			exit(0);
		room1->linkwith->room = room2;
	}
	else
	{
		if (room1->status == 's')
			linkwith_start(room1, room2);
		else
		{
			if (link_back(room1, room2->linkwith))
				return ;
			delete_linkwith_rooms(room1->linkwith);
			room1->linkwith = NULL;
			create_linkwith_list(room1, room2);
		}
	}
}

void	fill_room_linkwith(t_path *path)
{
	t_queue	*list;

	list = path->list;
	while (list && list->next)
	{
		create_linkwith_list(list->room, list->next->room);
		list = list->next;
	}
}
