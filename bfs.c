/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 17:57:30 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/13 12:40:29 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		bfs(t_farm *farm)
{
	t_room	*room;
	t_room	**queue;
	t_link	*link;
	int		endqueue;
	int		iter;

	if (!(queue = (t_room**)malloc(sizeof(t_room*) * farm->room_count)))
		return (0);
	iter = 0;
	endqueue = 1;
	farm->startroom = find_startend(farm->h_tab[farm->start].room, 's');
	farm->endroom = find_startend(farm->h_tab[farm->end].room, 'e');
	queue[iter] = farm->startroom;
	while (queue[iter])
	{
		room = queue[iter];
		link = room->link;
		while (link)
		{
			if (link->room->prev == NULL && link->room->status != 's')
			{
				queue[endqueue] = link->room;
				link->room->prev = room;
				if (link->room->status == 'e')
					return (1);
				endqueue++;
			}
			link = link->next;
		}
		iter++;
	}
	free(queue);
	ft_putstr("There is no end");
	return (0);
}
