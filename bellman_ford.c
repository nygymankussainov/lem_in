/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:52:47 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/10 19:41:57 by vhazelnu         ###   ########.fr       */
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
			if (room->dup)
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
			ret = link->room->status == 'e' ? 1 : ret;
			if (room->out && link->room->outroom == room)
			{
				link->room->visited = 1;
				link = link->next;
				continue ;
			}
			if (!link->lock && !link->room->visited && link->room->status != 'e')
				enqueue(queue, link->room, &last);
			if (!link->room->visited && !link->lock && room->dist + link->weight < link->room->dist)
			{
				link->room->dist = room->dist + link->weight;
				link->room->prev = room;
				// printf("%s-%s in %d\n", link->room->prev->name, link->room->name, link->room->dist);
				change = 1;
			}
			link = link->next;
		}
		dequeue(queue);
		room->visited = 1;
		room = *queue ? (*queue)->room : room;
	}
	ret = ret && change ? 2 : ret;
	return (ret);
}

int		bellman_ford(t_farm *farm)
{
	t_room	*room;
	t_queue	*queue;
	t_queue	*last;
	int		i;
	int		ret;

	i = 0;
	queue = NULL;
	last = NULL;
	assign_inf_dist(farm);
	while (i++ < farm->room_count - 1)
	{
		unvisit_rooms(farm);
		room = find_startend(farm->h_tab[farm->start].room, 's');
		enqueue(&queue, room, &last);
		ret = calculate_neg_dist(&queue, room, last);
		if (ret == 1)
			return (1);
		else if (!ret)
			return (0);
	}
	return (1);
}
