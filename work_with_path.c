/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 14:52:29 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/27 19:57:55 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		count_paths(t_queue *queue, t_room *room, t_queue *last, t_farm *farm)
{
	t_link	*link;
	int		i;
	int		j;

	i = 0;
	j = 0;
	enqueue(&queue, room, &last);
	unvisit_rooms(farm, 1);
	while (queue)
	{
		link = room->link;
		while (link)
		{
			if (!link->room->visited && !link->lock)
			{
				if (!link->room->status)
					enqueue(&queue, link->room, &last);
				link->room->visited = link->room->status != 'e' ? 1 : link->room->visited;
				if (room->status == 's')
					link->room->path1 = j;
				else if (!link->room->status)
					link->room->path1 = room->path1;
				if (link->room->status == 'e')
					i++;
				if (room->status != 's')
					break ;
				j++;
			}
			link = link->next;
		}
		dequeue(&queue);
		room = queue ? queue->room : room;
	}
	return (i);
}

void	reindex_paths(t_queue *queue, t_room *room, t_path *path)
{
	t_link	*link;
	t_queue *last;
	int		i;

	queue = NULL;
	last = NULL;
	enqueue(&queue, room, &last);
	i = 0;
	while (queue)
	{
		link = room->link;
		while (link)
		{
			if (!link->room->visited && !link->lock)
			{
				if (!link->room->status)
				{
					enqueue(&queue, link->room, &last);
					if (room->status == 's' && link->room->path1 == i)
					{
						link->room->path = path[i].index;
						i++;
					}
					else
						link->room->path = room->path;
				}
				link->room->visited = link->room->status != 'e' ? 1 : link->room->visited;
				if (room->status != 's')
					break ;
			}
			link = link->next;
		}
		dequeue(&queue);
		room = queue ? queue->room : room;
	}
}

void	sort_arr_path(t_path *path, int size)
{
	int		i;
	int		j;
	t_path	tmp;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (path[j].index == i)
				break ;
			j++;
		}
		tmp = path[i];
		path[i] = path[j];
		path[j] = tmp;
		i++;
	}
}

void	create_list_of_paths(t_room *room, t_path *path, int i)
{
	t_link	*link;
	t_queue	*queue;
	t_queue	*last;
	t_queue	*last1;

	queue = NULL;
	last = NULL;
	last1 = NULL;
	enqueue(&queue, room, &last);
	while (queue)
	{
		link = room->link;
		while (link)
		{
			if (!link->room->visited && !link->lock && link->room->path1 < 0)
			{
				enqueue(&path->list, link->room, &last1);
				path->steps++;
				path->index = i;
				link->room->path1 = i;
				if (!link->room->status)
					enqueue(&queue, link->room, &last);
				room->visited = room->status != 'e' ? 1 : room->visited;
				break ;
			}
			link = link->next;
		}
		dequeue(&queue);
		room = queue ? queue->room : room;
	}
}
