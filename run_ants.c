/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ants.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 17:57:58 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/05 19:14:42 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// int		check_lock(t_room *room, t_link *link)
// {
// 	t_room	*room_tmp;
// 	t_link	*link_tmp;

// 	room_tmp = link->room;
// 	link_tmp = room_tmp->link;
// 	if (!link->lock)
// 		return (0);
// 	if (!room->dup)
// 	{
// 		while (link_tmp && link_tmp->room != room)
// 			link_tmp = link_tmp->next;
// 		if (room_tmp->dup && room_tmp->in && !room->dup)
// 			link_tmp = room_tmp->outroom->link;
// 	}
// 	else if (room->dup && room->out)
// 		while (link_tmp && link_tmp->room->name != room->name)
// 			link_tmp = link_tmp->next;
// 	if (link_tmp && !link_tmp->lock)
// 		return (1);
// 	return (0);
// }

// void	run(t_queue *queue, t_room *room, t_queue *last)
// {
// 	t_link	*link;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	while (queue)
// 	{
// 		link = room->link;
// 		while (link)
// 		{
// 			if (room->outroom && room->outroom == link->room)
// 			{
// 				enqueue(&queue, link->room, &last);
// 				link->room->visited = 1;
// 				link = link->next;
// 				continue ;
// 			}
// 			if (!link->room->visited && check_lock(room, link))
// 			{
// 				enqueue(&queue, link->room, &last);
// 				link->room->visited = link->room-> status != 'e' ? 1 : link->room->visited;
// 				// printf("L%d-%s", j, link->room->name);
// 				i += room->status == 's' ? 1 : 0;
// 				j++;
// 				// if (j < i || (room->status == 's' && link->next))
// 					// printf(" ");
// 			}
// 			link = link->next;
// 		}
// 		dequeue(&queue);
// 		room = queue ? queue->room : room;
// 		if (j >= i)
// 		{
// 			j = 0;
// 			printf("\n");
// 		}
// 	}
// }

// void	run_ants(t_farm *farm)
// {
// 	t_room	*room;
// 	t_queue	*queue;
// 	t_queue	*last;

// 	queue = NULL;
// 	room = find_startend(farm->h_tab[farm->start].room, 's');
// 	last = NULL;
// 	enqueue(&queue, room, &last);
// 	run(queue, room, last);
// }
