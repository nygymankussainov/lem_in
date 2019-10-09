/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_prev_rooms.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:14:47 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/09 11:19:02 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	change_prev_rooms(t_room *room)
{
	t_link	*link;

	link = room->link;
	while (link)
	{
		if (link->room->name != room->name &&
			link->room->prev &&
			link->room->prev->name == room->name)
			link->room->prev = room;
		link = link->next;
	}
}

void	change_link_room(t_queue *list)
{
	t_link	*link;

	link = list->room->link;
	while (link)
	{
		if (link->room == list->prev->room)
		{
			link->room = !link->room->dup ?
				link->room : link->room->outroom;
			break ;
		}
		link = link->next;
	}
}
