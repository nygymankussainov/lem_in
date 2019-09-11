/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_shortest_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 17:04:26 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/11 15:30:24 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_free_path(t_farm *farm)
{
	t_room	*room;
	t_link	*link;

	room = find_startend(farm->h_tab[farm->start].room, 's');
	link = room->link;
	while (link)
	{
		if (!link->lock)
			return (1);
		link = link->next;
	}
	return (0);
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
			room = room->next;
		}
		tmp = tmp->next;
	}
}

t_room	*ft_roomcpy(t_room *room)
{
	t_room	*res;

	if (!(res = (t_room*)malloc(sizeof(t_room))))
		exit(0);
	res->antnbr = room->antnbr;
	res->x = room->x;
	res->y = room->y;
	res->dist = room->dist;
	res->pathlength = room->pathlength;
	res->name = room->name;
	res->status = room->status;
	res->visited = room->visited;
	if (!(res->link = (t_link*)malloc(sizeof(t_link))))
		exit(0);
	res->in = NULL;
	res->out = NULL;
	res->prev = room->prev;
	res->next = room->next;
	return (res);
}

// void	ft_make_room_duplicate(t_farm *farm, t_room *room)
// {
	
// }

// int		find_shortest_path(t_farm *farm)
// {
	
// }
