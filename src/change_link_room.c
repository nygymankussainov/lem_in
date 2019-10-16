/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_prev_rooms.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:14:47 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/16 14:28:52 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

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
