/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:53:35 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/26 16:06:26 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_graph(t_farm *farm)
{
	t_link	*link;
	t_queue	*queue;
	t_queue	*last;
	t_room	*room;

	unvisit_rooms(farm, 0);
	queue = NULL;
	last = NULL;
	room = farm->startroom;
	enqueue(&queue, room, &last);
	while (queue)
	{
		link = room->link;
		while (link)
		{
			if (!link->room->visited)
				enqueue(&queue, link->room, &last);
			// if (room->prev)
			// 	printf("%s is prev of ", room->prev->name);
			if (room->dup)
			{
				if (room->in)
					printf("%sin ", room->name);
				else if (room->out)
					printf("%sout ", room->name);
			}
			else
				printf("%s ", room->name);
			if (!link->lock)
				printf("- ");
			else
				printf("lock - ");
			if (link->room->dup)
			{
				if (link->room->in)
					printf("%sin", link->room->name);
				else if (link->room->out)
					printf("%sout", link->room->name);
			}
			else
				printf("%s", link->room->name);
			printf(" %d\n", link->weight);
			link = link->next;
		}
		room->visited = 1;
		dequeue(&queue);
		room = queue ? queue->room : room;
	}
}
