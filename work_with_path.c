/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 14:52:29 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/17 14:12:42 by vhazelnu         ###   ########.fr       */
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
		room = room->outroom ? room->outroom : room;
		link = room->link;
		while (link)
		{
			if (!link->room->visited && check_lock(room, link))
			{
				if (!link->room->status)
					enqueue(&queue, link->room, &last);
				link->room->visited = link->room->status != 'e' ? 1 : link->room->visited;
				if (room->status == 's')
					link->room->dist = j;
				else if (!link->room->status)
					link->room->dist = room->dist;
				if (link->room->inroom)
					link->room->inroom->dist = link->room->dist;
				else if (link->room->outroom)
					link->room->outroom->dist = link->room->dist;
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

void	count_steps(t_queue *queue, t_room *room, t_queue *last, t_path *path)
{
	t_link	*link;

	queue = NULL;
	last = NULL;
	enqueue(&queue, room, &last);
	while (queue)
	{
		room = room->outroom ? room->outroom : room;
		link = room->link;
		while (link)
		{
			if (!link->room->visited && check_lock(room, link))
			{
				if (!link->room->status)
				{
					enqueue(&queue, link->room, &last);
					path[link->room->dist].steps += !path[link->room->dist].steps ? 1 : 0;
					path[link->room->dist].steps++;
					path[link->room->dist].index = link->room->dist;
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
		room = room->outroom ? room->outroom : room;
		link = room->link;
		while (link)
		{
			if (!link->room->visited && check_lock(room, link))
			{
				if (!link->room->status)
				{
					enqueue(&queue, link->room, &last);
					if (room->status == 's' && link->room->dist == i)
					{
						link->room->path = path[i].index;
						i++;
					}
					else
						link->room->path = room->path;
					if (link->room->inroom)
						link->room->inroom->path = link->room->path;
					else if (link->room->outroom)
						link->room->outroom->path = link->room->path;
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

void	create_queue_of_paths(t_queue *queue, t_path *path, t_room *room, int size)
{
	t_link	*link;
	t_queue	*last1;
	t_queue	*last2;
	t_room	*start;
	int		i;

	i = 0;
	start = room;
	while (i < size)
	{
		queue = NULL;
		last1 = NULL;
		last2 = NULL;
		room = start;
		enqueue(&queue, room, &last1);
		while (queue)
		{
			room = room->outroom ? room->outroom : room;
			link = room->link;
			while (link)
			{
				if ((link->room->path == i || link->room->status == 'e') && !link->room->visited && check_lock(room, link))
				{
					// if (room->status == 's')
					// 	enqueue(&path[link->room->path].queue, room, &last2);
					if (!link->room->status)
					{
						enqueue(&queue, link->room, &last1);
						enqueue(&path[link->room->path].queue, link->room, &last2);
					}
					else
					{
						if (room->path < 0)
							room->path = 0;
						enqueue(&path[room->path].queue, link->room, &last2);
					}
					if (link->room->status != 'e')
					{
						last2->index = path[link->room->path].index;
						last2->steps = path[link->room->path].steps;
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
		i++;
	}
}
