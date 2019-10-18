/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_link_room.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:14:47 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/18 13:21:22 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** This function is made for end-vertex,
** after some room that links with end-vertex has duplicated
** it changes the link end-room(in) to duplicated
** room end-room(out).
*/

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
