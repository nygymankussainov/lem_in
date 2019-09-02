/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 17:57:30 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/02 16:47:26 by vhazelnu         ###   ########.fr       */
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
		(*last) = (*queue);
	}
	else
	{
		if (!(new = (t_queue *)ft_memalloc(sizeof(t_queue))))
			exit(0);
		new->room = room;
		(*last)->next = new;
		(*last) = new;
	}
}

t_room	*find_startend(t_room *room, char c)
{
	while (room)
	{
		if (room->status == c)
			return (room);
		room = room->next;
	}
	return (NULL);
}

int		calculate_distance(t_queue *queue, t_room *room, t_queue *last)
{
	t_link	*link;
	int		ret;
	int		tmp;

	ret = 0;
	while (queue)
	{
		tmp = 0;
		link = room->link;
		ret = room->status == 'e' ? 1 : ret;
		printf("%s: ", room->name);
		while (link)
		{
			if (!link->lock && !link->room->visited && link->room->status != 's')
			{
				enqueue(&queue, link->room, &last);
				if (link->room->dist == 0 || room->dist + link->weight < link->room->dist)
					link->room->dist = room->dist + link->weight;
				if (link->room->dist <= tmp || !tmp || !link->room->dist || link->room->status == 'e')
					link->room->prev = room;
				tmp = link->room->dist;
				// printf("%s-%s %d\n", link->room->name, link->room->prev->name, link->room->dist);
				link->room->visited = link->room->status == 'e' ? link->room->visited : 1;
				printf("%s-", link->room->name);
				printf("%s\n", link->room->prev->name);
				// link->room->visited = 1;
			}
			link = link->next;
		}
		dequeue(&queue);
		room = queue ? queue->room : room;
	}
	// printf("\n");
	return (ret);
}

int		bfs(t_farm *farm)
{
	t_queue	*queue;
	t_queue	*last;
	t_room	*room;

	queue = NULL;
	room = find_startend(farm->h_tab[farm->start].room, 's');
	enqueue(&queue, room, &last);
	if (calculate_distance(queue, room, last))
		return (1);
	return (0);
}
