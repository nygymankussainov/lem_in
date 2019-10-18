/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_intersecting_links.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 14:43:28 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/18 14:43:33 by vhazelnu         ###   ########.fr       */
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

void	lock_intersecting_links(t_path *new)
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
