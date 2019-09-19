/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_enough_paths.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:41:34 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/18 20:57:13 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_enough_paths(t_farm *farm, int i)
{
	t_link	*link;
	t_room	*room;
	t_queue	*queue;
	t_queue	*last;
	int		steps;

	if (i < 2)
		return (1);
	queue = NULL;
	last = NULL;
	room = farm->startroom;
	enqueue(&queue, room, &last);
	steps = 0;
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
					steps++;
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
	unvisit_rooms(farm, 0);
	if (farm->ants > steps)
		return (1);
	return (0);
}

// int		is_enough_paths(t_farm *farm, int steps)
// {
// 	t_room	*room;
// 	t_room	*prev;
// 	t_link	*link;
// 	int		i;
// 	int		j;

// 	room = farm->startroom;
// 	link = room->link;
// 	i = 0;
// 	j = 0;
// 	while (link)
// 	{
// 		if (check_lock(room, link))
// 			i++;
// 		link = link->next;
// 	}
// 	room = farm->endroom;
// 	while (room && room->status != 's')
// 	{
// 		room = room->prev;
// 		j++;
// 	}
// 	if (farm->ants - i > j + j - steps)
// 		return (j + steps);
// 	return (0);
// }
