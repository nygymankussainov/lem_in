/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_pathes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 14:20:12 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/12 21:37:17 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_room	*ft_roomcpy(t_room *room)
{
	t_room	*res;

	if (!(res = (t_room*)malloc(sizeof(t_room))))
		exit(0);
	res->antnbr = room->antnbr;
	res->dist = room->dist;
	res->name = room->name;
	res->status = room->status;
	if (!(res->link = (t_link*)malloc(sizeof(t_link))))
		exit(0);
	res->in = NULL;
	res->out = NULL;
	res->prev = room->prev;
	res->next = room->next;
	res->parent = room;
	return (res);
}

t_room	*ft_find_next_room(t_room *room)
{
	t_link *tmplink;

	tmplink = room->link;
	while (tmplink && tmplink->room->prev != room)
		tmplink = tmplink->next;
	return (tmplink->room);
}

void	ft_create_out_link(t_room *out, t_link **linkout, t_room *room)
{
	t_link	*link;
	t_link	*newlink;
	t_room	*need_find;

	(*linkout)->room = room;
	(*linkout)->weight = 1;
	link = room->link;
	need_find = (ft_find_next_room(out->parent) == room) ? room : NULL; // если это next_room, то in не занял линк
	// if (need_find == NULL)
	// {
		// while (link->next)
			// link = link->next;
		// if (!(link->next = (t_link*)malloc(sizeof(t_link))))
			// exit(0);
		// link = link->next;
	// }
	// else
		while (link && link->room != out->parent)
			link = link->next;
	// if (!link)
		
	link->room = out;
	link->lock = 1;
	if (!(newlink = (t_link*)malloc(sizeof(t_link))))
		exit(0);
	(*linkout)->next = newlink;
	(*linkout) = newlink;
}

void	ft_create_in_link(t_room *in, t_link **linkin, t_room *room)
{
	t_link	*link;
	t_link	*newlink;

	(*linkin)->room = room;
	(*linkin)->lock = 1;
	link = room->link;
	while (link && link->room != in->parent)
		link = link->next;
	link->room = in;
	link->weight = 1;
	if (!(newlink = (t_link*)malloc(sizeof(t_link))))
		exit(0);
	(*linkin)->next = newlink;
	(*linkin) = (*linkin)->next;
}

void	ft_make_room_duplicate(t_room *room)
{
	t_link	*link;
	t_link	*linkout;
	t_link	*linkin;
	t_room	*nextroom;

	room->in = ft_roomcpy(room);
	room->out = ft_roomcpy(room);
	room->in->induplicate = true;
	room->out->outduplicate = true;
	linkout = room->out->link;
	linkin = room->in->link;
	link = room->link;
	nextroom = ft_find_next_room(room);
	while (link)
	{
		if (link->room != nextroom)
			ft_create_in_link(room->in, &linkin, link->room); // я не ебу почему амперсанд!!!!
		if (link->room != room->prev)
			ft_create_out_link(room->out, &linkout, link->room);
		link = link->next;
	}
	linkout->room = room->in;
	linkout->weight = 0;
	linkin->room = room->out;
	linkin->lock = 1;
}

void	ft_make_rooms_duplicates(t_farm *farm)
{
	t_room	*tmproom;

	tmproom = farm->endroom->prev;
	while (tmproom != farm->startroom)
	{
		if (tmproom->in == NULL && tmproom->out == NULL)
		{
			ft_make_room_duplicate(tmproom);
			farm->duplicate_count++;
		}
		tmproom = tmproom->prev;
	}
}

void    ft_reverse_shortest_path(t_farm *farm)
{
	t_room  *tmproom;
	t_link	*link;

	tmproom = farm->endroom;
	while (tmproom != farm->startroom)
	{
		link = tmproom->link;
		while (link->room != tmproom->prev)
			link = link->next;
		link->weight = -1;
		link = tmproom->prev->link;
		// ft_printf("%s-", tmproom->name);
		while (link && link->room != tmproom)
			link = link->next;
		link->lock = 1;
		tmproom = tmproom->prev;
	}
	// ft_printf("%s\n", tmproom->name);
}
