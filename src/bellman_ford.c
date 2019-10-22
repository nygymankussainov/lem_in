/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:52:47 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/22 15:04:10 by vhazelnu         ###   ########.fr       */
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

/*
** In calculate_neg_dist() function we are finding
** the closest path from start-room to end-room.
*/

int		calculate_neg_dist(t_queue **queue, t_room *room, t_queue *last)
{
	t_link	*link;
	int		ret;

	ret = 0;
	while (*queue)
	{
		link = room->link;
		while (link && room->status != 'e')
		{
			if (change_dist(link, room, queue, &last))
				ret = link->room->status == 'e' ? 1 : ret;
			link = link->next;
		}
		dequeue(queue);
		room->visited = 1;
		room = *queue ? (*queue)->room : room;
	}
	return (ret);
}

/*
** In preparation() function we duplicate
** intermediate rooms of found paths
** and reverse (make directed from end to start) edges of these paths in
** manage_direction() function.
*/

void	preparation(t_path *path, t_farm *farm)
{
	int		i;

	i = 0;
	create_dup_rooms(path);
	while (i < path->size)
		manage_direction(path + i++, 1);
	assign_inf_dist(farm);
}

/*
** The bellman_ford() function calculates distance
** from start vertex to every other vertex
** only once instead of N-1 times,
** because in this project we have graphs with
** unweighted edges.
*/

int		bellman_ford(t_farm *farm, t_path *path)
{
	t_queue	*queue;
	t_queue	*last;

	queue = NULL;
	last = NULL;
	preparation(path, farm);
	unvisit_rooms(farm, 0);
	enqueue(&queue, farm->startroom, &last);
	if (calculate_neg_dist(&queue, farm->startroom, last))
		return (1);
	return (delete_dup_rooms(path));
}
