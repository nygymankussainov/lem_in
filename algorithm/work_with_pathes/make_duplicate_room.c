/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_duplicate_room.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 21:22:38 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/25 13:34:27 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*ft_find_next_room(t_room *room)
{
	t_link *tmplink;

	tmplink = room->link;
	while (tmplink)
	{
		if (tmplink->room->prev == room
		&& tmplink->room->pathnbr == room->pathnbr)
			break ;
		tmplink = tmplink->next;
	}
	return (tmplink->room);
}

void	ft_make_room_duplicate(t_room *room)
{
	t_link	*link;
	t_link	*linkout;
	t_link	*linkin;
	t_room	*nextroom;

	ft_init_duplicates(&room, &linkout, &linkin);
	link = room->link;
	nextroom = ft_find_next_room(room);
	while (link)
	{
		if (ft_strcmp(link->room->name, nextroom->name) != 0)
			ft_create_in_link(room->in, &linkin, link->room, nextroom);
		if (ft_strcmp(link->room->name, room->prev->name) != 0)
			ft_create_out_link(room->out, &linkout, link->room, nextroom);
		link = link->next;
	}
	ft_connect_in_and_out(&linkout, &linkin, room);
}

void	ft_make_rooms_duplicates(t_farm *farm)
{
	t_room	*tmproom;

	tmproom = farm->endroom->prev;
	while (tmproom != farm->startroom)
	{
		if (tmproom->in == NULL && tmproom->out == NULL &&
			tmproom->induplicate == false && tmproom->outduplicate == false)
		{
			ft_make_room_duplicate(tmproom);
			farm->duplicate_count++;
		}
		tmproom = tmproom->prev;
	}
}
