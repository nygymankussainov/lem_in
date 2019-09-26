/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_shortest_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 18:38:35 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/26 19:51:14 by vhazelnu         ###   ########.fr       */
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

void	unvisit_rooms(t_farm *farm, int i)
{
	t_hashcodes	*tmp;
	t_room		*room;

	tmp = farm->hashcodes;
	while (tmp)
	{
		room = farm->h_tab[tmp->hash_code].room;
		while (room)
		{
			room->antnbr = i == 2 ? -1 : room->antnbr;
			room->path1 = i == 1 ? -1 : room->path1;
			room->visited = 0;
			if (room->outroom)
			{
				room->outroom->antnbr = i == 2 ? -1 : room->outroom->antnbr;
				room->outroom->visited = 0;
				room->outroom->path1 = i == 1 ? -1 : room->outroom->path1;
			}
			room = room->next;
		}
		tmp = tmp->next;
	}
}

// void	connect_two_dup_rooms(t_room *room, t_link *link1)
// {
// 	t_link	*out1;
// 	t_link	*out2;

// 	link1->room = room->outroom;
// 	link1->lock = 1;
// 	room->link = link1;
// 	out1 = room->outroom->link;
// 	while (out1->room->name != room->prev->name)
// 		out1 = out1->next;
// 	out1->lock = 0;
// 	out1->weight = -1;
// 	out2 = out1->room->outroom->link;
// 	while (out2->room != room)
// 		out2 = out2->next;
// 	out2->lock = 0;
// 	out2->weight = -1;
// }

// int		create_link(t_room *room, int i)
// {
// 	t_link	*link1;
// 	t_link	*link2;
// 	t_link	*out;

// 	if (!(link1 = (t_link *)ft_memalloc(sizeof(t_link))) ||
// 		!(link2 = (t_link *)ft_memalloc(sizeof(t_link))))
// 		exit(0);
// 	if (i)
// 	{
// 		connect_two_dup_rooms(room, link1);
// 		return (1);
// 	}
// 	out = room->outroom ? room->outroom->link : room->link;
// 	link1->room = room->outroom;
// 	link1->lock = 1;
// 	while (out && out->room != room->prev)
// 		out = out->next;
// 	// if (!out)
// 	// {
// 	// 	free(link1);
// 	// 	free(link2);
// 	// 	return (0);
// 	// }
// 	link2->room = out->room;
// 	link2->weight = -1;
// 	link2->lock = 0;
// 	link1->next = link2;
// 	room->link = link1;
// 	out->room = room;
// 	out->weight = 0;
// 	out->room->path = -1;
// 	return (1);
// }

// int		create_dup_room(t_farm *farm, t_room *clone)
// {
// 	t_room	*room;
// 	t_room	*end;
// 	int		i;

// 	i = 0;
// 	end = farm->endroom;
// 	while (end != clone)
// 		end = end->prev;
// 	room = end->prev;
// 	if (!room->dup && room->prev->dup)
// 		i = 1;
// 	if (!room->dup)
// 	{
// 		if (!(room->outroom = (t_room *)ft_memalloc(sizeof(t_room))))
// 			exit(0);
// 		room->outroom->name = room->name;
// 		room->outroom->link = room->link;
// 		room->outroom->inroom = room;
// 		room->outroom->prev = room;
// 		room->link = NULL;
// 		room->in = 1;
// 		room->outroom->dup = 1;
// 		room->dup = 1;
// 		room->outroom->out = 1;
// 	}
// 	if (!create_link(room, i))
// 		return (0);
// 	return (1);
// }

// int		find_shortest_path(t_farm *farm, t_path **path, int ret)
// {
// 	t_room	*room;
// 	t_room	*tmp;
// 	t_link	*link;
// 	t_room	*main_room;

// 	room = farm->endroom;
// 	main_room = room;
// 	link = room->link;
// 	if (room->status == 's')
// 		ret = 0;
// 	while (room->status != 's')
// 	{
// 		if (main_room->prev->status != 's' && ret > 1 && !main_room->prev)
// 		{
// 			if (!create_dup_room(farm, main_room))
// 				return (0);
// 		}
// 		link = room->inroom ? room->inroom->link : room->link;
// 		while (link->room != main_room->prev)
// 		{
// 			link = link->next;
// 			if (!link)
// 				link = room->inroom ? room->inroom->link : room->outroom->link;
// 		}
// 		link->room = link->room->outroom ? link->room->outroom : link->room;
// 		link->weight = -1;
// 		tmp = room->inroom ? room->inroom : room;
// 		room = link->room;
// 		main_room = link->room->inroom ? link->room->inroom : link->room;
// 		link = room->link;
// 		while (link->room != tmp)
// 		{
// 			link = link->next;
// 			if (!link)
// 				link = room->inroom ? room->inroom->link : room->outroom->link;
// 		}
// 		link->lock = 1;
// 		if (!main_room->prev->dup && !main_room->prev->status)
// 		{
// 			main_room = main_room->prev;
// 			room = main_room;
// 		}
// 	}
// 	if (!create_paths(farm, path))
// 		return (0);
// 	return (ret);
// }
