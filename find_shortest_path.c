/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_shortest_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nygymankussainov <nygymankussainov@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 17:04:26 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/03 12:50:22 by nygymankuss      ###   ########.fr       */
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

int		find_shortest_path(t_farm *farm)
{
	t_room	*room;
	t_room	*tmp;
	t_link	*link;
	int		ret;

	room = find_startend(farm->h_tab[farm->end].room, 'e');
	link = room->link;
	if (!(ret = is_free_path(farm)))
		return (0);
	while (room->status != 's')
	{
		link = room->link;
		printf("%s-", room->name);
		while (link->room != room->prev)
			link = link->next;
		link->weight = -1;
		tmp = room;
		room = link->room;
		link = room->link;
		while (link->room != tmp)
			link = link->next;
		link->lock = 1;
	}
	printf("%s\n", room->name);
	return (ret);
}
