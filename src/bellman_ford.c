/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:52:47 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/17 14:05:02 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	assign_inf_dist(t_farm *farm)
{
	t_hashcodes	*tmp;
	t_room		*room;

	tmp = farm->hashcodes;
	while (tmp)
	{
		room = farm->h_tab[tmp->hash_code].room;
		while (room)
		{
			room->dist = room->status != 's' ? INT_MAX : room->dist;
			if (room->outroom)
				room->outroom->dist = INT_MAX;
			room = room->next;
		}
		tmp = tmp->next;
	}
}

bool	change_dist(t_link *link, t_room *room, t_queue **queue, t_queue **last)
{
	if (!link->lock && !link->room->visited
		&& link->room->status != 'e')
		enqueue(queue, link->room, last);
	if (!link->lock && room->dist + link->weight < link->room->dist
		&& link->room->status != 's')
	{
		link->room->dist = room->dist + link->weight;
		link->room->prev = room;
		return (1);
	}
	return (0);
}

int		calculate_neg_dist(t_queue **queue, t_room *room, t_queue *last)
{
	t_link	*link;
	bool	change;
	int		ret;

	change = 0;
	ret = 0;
	while (*queue)
	{
		link = room->link;
		while (link && room->status != 'e')
		{
			if (change_dist(link, room, queue, &last))
			{
				ret = link->room->status == 'e' ? 1 : ret;
				change = 1;
			}
			link = link->next;
		}
		dequeue(queue);
		room->visited = 1;
		room = *queue ? (*queue)->room : room;
	}
	return (ret && change ? 2 : ret);
}

/*
** Here in manage_direction() function on line 95 we
** reverse (make directed from end to start) edges in path(s)
*/

int		bellman_ford(t_farm *farm, t_path *path)
{
	t_queue	*queue;
	t_queue	*last;
	int		i;
	int		ret;
	int		isend;

	i = 0;
	queue = NULL;
	last = NULL;
	create_dup_rooms(path);
	while (i < path->size)
		manage_direction(path + i++, 1);
	assign_inf_dist(farm);
	i = 0;
	isend = 0;
	while (i++ < farm->room_count - 1)
	{
		unvisit_rooms(farm, 0);
		enqueue(&queue, farm->startroom, &last);
		if ((ret = calculate_neg_dist(&queue, farm->startroom, last)) == 1)
			return (1);
		else if (ret == 2)
			isend = 1;
		else if (!ret)
		{
			if (!isend)
				return (delete_dup_rooms(path));
			return (1);
		}
	}
	return (1);
}
