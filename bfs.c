/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 17:57:30 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/14 12:15:20 by vhazelnu         ###   ########.fr       */
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
		new = *queue;
		while (new)
		{
			if (new->room == room)
				return ;
			new = new->next;
		}
		if (!(new = (t_queue *)ft_memalloc(sizeof(t_queue))))
			exit(0);
		new->room = room;
		(*last)->next = new;
		*last = new;
	}
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
			}
			link = link->next;
		}
		dequeue(&queue);
		room = queue ? queue->room : room;
	}
	return (ret);
}

int		bfs(t_farm *farm)
{
	t_queue	*queue;
	t_queue	*last;
	int		ret;

	queue = NULL;
	last = NULL;
	ret = ft_count_paths(farm);
	enqueue(&queue, farm->startroom, &last);
	if (calculate_distance(queue, farm->startroom, last))
	{
		if (!find_shortest_path(farm, ret))
			return (0);
		return (ret);
	}
	return (-1);
}
