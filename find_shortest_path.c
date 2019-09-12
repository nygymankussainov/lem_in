/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_shortest_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 18:38:35 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/12 21:20:28 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_count_paths(t_farm *farm)
{
	int		start;
	int		end;
	t_link  *link;

	end = 0;
	start = 0;
	link = farm->startroom->link;
	while (link)
	{
		link = link->next;
		start++;
	}
	link = farm->endroom->link;
	while (link)
	{
		end++;
		link = link->next;
	}
	return ((start < end) ? start : end);
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
			if (room->outroom)
				room->outroom->visited = 0;
			room = room->next;
		}
		tmp = tmp->next;
	}
}

int		create_link(t_room *room)
{
	t_link	*link1;
	t_link	*link2;
	t_link	*out;

	if (!(link1 = (t_link *)ft_memalloc(sizeof(t_link))) ||
		!(link2 = (t_link *)ft_memalloc(sizeof(t_link))))
		exit(0);
	out = room->outroom->link;
	link1->room = room->outroom;
	link1->lock = 1;
	while (out && out->room != room->prev)
		out = out->next;
	if (!out)
		return (0);
	link2->room = out->room;
	link2->weight = -1;
	link2->lock = 0;
	link1->next = link2;
	room->link = link1;
	out->room = room;
	out->lock = 1;
	out->weight = 0;
	return (1);
}

int		create_dup_room(t_farm *farm, t_room *clone)
{
	t_room	*room;
	t_room	*end;

	end = find_startend(farm->h_tab[farm->end].room, 'e');
	while (end != clone)
		end = end->prev;
	room = end->prev;
	if (!room->outroom)
	{
		if (!(room->outroom = (t_room *)ft_memalloc(sizeof(t_room))))
			exit(0);
		room->outroom->name = room->name;
		room->outroom->link = room->link;
		room->outroom->inroom = room;
		room->link = NULL;
		room->in = 1;
		room->outroom->out = 1;
	}
	if (!create_link(room))
		return (0);
	return (1);
}

int		find_shortest_path(t_farm *farm, int ret)
{
	t_room	*room;
	t_room	*tmp;
	t_link	*link;
	t_room	*main_room;

	room = find_startend(farm->h_tab[farm->end].room, 'e');
	main_room = room;
	link = room->link;
	if (room->status == 's')
		ret = 0;
	while (room->status != 's')
	{
		if (main_room->prev->status != 's' && ret > 1)
			if (!create_dup_room(farm, main_room))
				return (0);
		link = room->link;
		printf("%s-", room->name);
		while (link->room != main_room->prev && link->room->name != main_room->prev->name)
		{
			link = link->next;
			if (!link)
				link = room->inroom ? room->inroom->link : room->outroom->link;
		}
		link->room = link->room->outroom ? link->room->outroom : link->room;
		link->weight = -1;
		tmp = room;
		room = link->room;
		main_room = link->room->inroom ? link->room->inroom : link->room;
		link = room->link;
		while (link->room->name != tmp->name)
		{
			link = link->next;
			if (!link)
				link = room->inroom ? room->inroom->link : room->outroom->link;
		}
		link->lock = 1;
	}
	printf("%s\n", room->name);
	return (ret);
}
