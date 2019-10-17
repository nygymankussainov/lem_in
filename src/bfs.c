/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 17:57:30 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/17 18:40:13 by vhazelnu         ###   ########.fr       */
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
		new->prev = *last;
		new->room = room;
		(*last)->next = new;
		*last = new;
	}
}

int		enqueue_to_begin(t_queue **queue, t_room *room)
{
	t_queue	*new;

	if (!*queue)
	{
		if (!(*queue = (t_queue *)ft_memalloc(sizeof(t_queue))))
			exit(0);
		(*queue)->room = room;
	}
	else
	{
		new = *queue;
		while (new)
		{
			if (new->room->name == room->name)
				return (1);
			new = new->next;
		}
		if (!(new = (t_queue *)ft_memalloc(sizeof(t_queue))))
			exit(0);
		(*queue)->prev = new;
		new->room = room;
		new->next = *queue;
		*queue = new;
	}
	return (0);
}

int		calculate_distance(t_queue *queue, t_room *room, t_queue *last)
{
	t_link	*link;
	int		ret;

	ret = 0;
	while (queue)
	{
		link = room->link;
		while (link)
		{
			ret = link->room->status == 'e' ? 1 : ret;
			if (!link->room->visited && link->room->status != 's')
			{
				enqueue(&queue, link->room, &last);
				link->room->dist = room->dist + link->weight;
				link->room->visited = 1;
				link->room->prev = link->room->status != 's' ? room : NULL;
			}
			link = link->next;
		}
		dequeue(&queue);
		room = queue ? queue->room : room;
	}
	return (ret);
}

int		bfs(t_farm *farm, t_path **path)
{
	t_queue	*queue;
	t_queue	*last;

	queue = NULL;
	last = NULL;
	farm->max_paths = ft_count_paths(farm);
	enqueue(&queue, farm->startroom, &last);
	if (!calculate_distance(queue, farm->startroom, last))
		return (-1);
	return (create_paths(farm, path));
}
