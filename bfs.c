/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nygymankussainov <nygymankussainov@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 17:57:30 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/03 12:49:05 by nygymankuss      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	dequeue(t_queue **queue)
{
	t_queue *head;

	head = *queue;
	*queue = (*queue)->next;
	free(head);
	head = NULL;
}

void	enqueue(t_queue **queue, t_room *room, t_queue **last)
{
	t_queue	*new;

	if (!*queue)
	{
		if (!(*queue = (t_queue *)ft_memalloc(sizeof(t_queue))))
			exit(0);
		(*queue)->room = room;
		*last = *queue;
	}
	else
	{
		if (!(new = (t_queue *)ft_memalloc(sizeof(t_queue))))
			exit(0);
		new->room = room;
		(*last)->next = new;
		*last = new;
	}
}

t_room	*find_startend(t_room *room, char c)
{
	while (room)
	{
		if (room->status == c)
		{
			room->visited = c == 's' ? 1 : room->visited;
			return (room);
		}
		room = room->next;
	}
	return (NULL);
}

int		calculate_distance(t_queue *queue, t_room *room, t_queue *last)
{
	t_link	*link;
	int		ret;

	ret = 0;
	while (queue)
	{
		link = room->link;
		ret = link->room->status == 'e' ? 1 : ret;
		while (link)
		{
			if (!link->room->visited)
			{
				enqueue(&queue, link->room, &last);
				link->room->dist = room->dist + link->weight;
				link->room->visited = 1;
				link->room->prev = room;
				printf("%s-%s in %d\n", link->room->prev->name, link->room->name, link->room->dist);
			}
			link = link->next;
		}
		dequeue(&queue);
		room = queue ? queue->room : room;
	}
	printf("\n");
	return (ret);
}

int		bfs(t_farm *farm)
{
	t_room	*room;
	t_queue	*queue;
	t_queue	*last;

	queue = NULL;
	room = find_startend(farm->h_tab[farm->start].room, 's');
	last = NULL;
	enqueue(&queue, room, &last);
	if (calculate_distance(queue, room, last))
		return (1);
	return (0);
}
