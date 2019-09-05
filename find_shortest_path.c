/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_shortest_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 17:04:26 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/05 18:20:59 by vhazelnu         ###   ########.fr       */
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
			room = room->next;
		}
		tmp = tmp->next;
	}
}

void	create_dup_room(t_farm *farm, t_room *clone)
{
	t_room	*room;
	t_room	*end;

	end = find_startend(farm->h_tab[farm->end].room, 'e');
	while (end != clone)
		end = end->prev;
	room = end->prev;
	if (!room->dup)
	{
		if (!(room->dup = (t_room *)ft_memalloc(sizeof(t_room))))
			exit(0);
		room->dup->name = room->name;
		room->dup->link = room->link;
		room->link = NULL;
		room->in = 1;
		room->dup->out = 1;
	}
}

void	find_shortest_path(t_farm *farm, int ret)
{
	t_room	*room;
	t_room	*tmp;
	t_link	*link;
	t_room	*main_room;

	room = find_startend(farm->h_tab[farm->end].room, 'e');
	main_room = room;
	link = room->link;
	while (room->status != 's')
	{
		if (main_room->prev->status != 's' && ret > 1)
			create_dup_room(farm, main_room);
		link = room->link;
		// printf("%s-", room->name);
		while (link->room != main_room->prev)
			link = link->next;
		link->weight = -1;
		tmp = room;
		room = main_room->prev->status != 's' && link->room->dup ? link->room->dup : main_room->prev;
		main_room = link->room;
		link = room->link;
		while (link->room->name != tmp->name)
			link = link->next;
		link->lock = 1;
	}
	// printf("%s\n", room->name);
}
