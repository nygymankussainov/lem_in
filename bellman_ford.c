/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:52:47 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/27 18:37:17 by vhazelnu         ###   ########.fr       */
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
			if (link->room)
				ret = link->room->status == 'e' ? 1 : ret;
			if (!link->lock && !link->room->visited && link->room->status != 'e')
				enqueue(queue, link->room, &last);
			if (!link->lock && room->dist + link->weight < link->room->dist
				&& link->room->status != 's')
			{
				link->room->dist = room->dist + link->weight;
				if (link->room->inroom)
				{
					link->room->inroom->dist = link->room->dist;
					link->room->inroom->prev = room;
				}
				else if (link->room->outroom)
				{
					link->room->outroom->dist = link->room->dist;
					link->room->outroom->prev = room;
				}
				link->room->prev = room;
				change = 1;
			}
			link = link->next;
		}
		dequeue(queue);
		room->visited = 1;
		if (room->inroom)
			room->inroom->visited = 1;
		else if (room->outroom)
			room->outroom->visited = 1;
		room = *queue ? (*queue)->room : room;
	}
	ret = ret && change ? 2 : ret;
	return (ret);
}

int		bellman_ford(t_farm *farm, t_path *path)
{
	t_queue	*queue;
	t_queue	*last;
	int		i;
	int		ret;

	i = 0;
	queue = NULL;
	last = NULL;
	create_dup_rooms(path);
	while (i < path->size)
		manage_direction(&path[i++], 1);
	// printf("AFTER DUPLICATE\n");
	// print_graph(farm);
	assign_inf_dist(farm);
	i = 0;
	while (i++ < farm->room_count - 1)
	{
		unvisit_rooms(farm, 0);
		enqueue(&queue, farm->startroom, &last);
		ret = calculate_neg_dist(&queue, farm->startroom, last);
		if (ret == 1)
		{
			delete_dup_rooms(path);
			return (1);
		}
		else if (!ret)
		{
			delete_dup_rooms(path);
			// printf("BEFORE DUPLICATE\n");
			// print_graph(farm);
			return (0);
		}
	}
	delete_dup_rooms(path);
	return (1);
}
