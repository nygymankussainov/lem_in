/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_collided_links.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:03:09 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/17 14:06:03 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	lock_reverse_link(t_room *room1, t_room *room2)
{
	t_link	*link;

	link = room2->link;
	while (link && link->room != room1)
		link = link->next;
	link->lock = 1;
	link->go = 0;
}

void	lock_collided_links(t_path *new)
{
	t_link	*link;
	t_queue	*list;

	list = new->list;
	while (list && list->next)
	{
		link = list->room->link;
		while (link && link->room != list->next->room)
			link = link->next;
		if (link->lock)
			link->go = 0;
		else
			link->go = 1;
		lock_reverse_link(list->room, link->room);
		list = list->next;
	}
}
