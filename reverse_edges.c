/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_edges.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 19:02:43 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/24 19:29:44 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	reverse_edge(t_room *room, t_link *link, int lock)
{
	t_link	*rev_link;

	link->lock = lock == 1 ? 0 : 1;
	rev_link = link->room->link;
	while (rev_link)
	{
		if (rev_link->room == room)
		{
			rev_link->lock = 1;
			return ;
		}
		rev_link = rev_link->next;
	}
}

void	reverse_edges(t_farm *farm)
{
	t_link	*link;
	t_queue	*queue;
	t_queue	*last;
	t_room	*room;
	int		lock;

	queue = NULL;
	last = NULL;
	room = farm->startroom;
	enqueue(&queue, room, &last, 0);
	while (queue)
	{
		link = room->link;
		while (link)
		{
			if (!link->room->visited)
			{
				lock = check_lock(room, link);
				if (lock != 0)
					reverse_edge(room, link, lock);
				enqueue(&queue, link->room, &last, 0);
			}
			else
				link->lock = 1;
			link = link->next;
		}
		room->visited = 1;
		dequeue(&queue);
		room = queue ? queue->room : room;
	}
}
