/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_shortest_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 17:04:26 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/25 13:38:29 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_free_path(t_farm *farm)
{
	t_room	*room;
	t_link	*link;
	int		i;

	i = 0;
	room = find_startend(farm->h_tab[farm->start].room, 's');
	link = room->link;
	while (link)
	{
		if (!link->lock)
			i++;
		link = link->next;
	}
	return (i);
}

void	unvisit_rooms(t_farm *farm)
{
	t_hashcodes	*tmp;
	t_room		*room;

	tmp = farm->hashcodes;
	while (tmp)
	{
		room = farm->h_tab[tmp->hash_code].room;
		while (room)
		{
			room->visited = 0;
			if (room->in)
			{
				room->in->visited = 0;
				room->out->visited = 0;
			}
			room = room->next;
		}
		tmp = tmp->next;
	}
}
