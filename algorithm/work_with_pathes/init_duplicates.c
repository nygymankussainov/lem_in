/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_duplicates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:18:22 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/17 22:09:55 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*ft_roomcpy(t_room *room)
{
	t_room	*res;

	if (!(res = (t_room*)malloc(sizeof(t_room))))
		exit(0);
	res->antnbr = room->antnbr;
	res->dist = room->dist;
	res->name = room->name;
	res->status = room->status;
	res->pathnbr = room->pathnbr;
	if (!(res->link = (t_link*)malloc(sizeof(t_link))))
		exit(0);
	res->in = NULL;
	res->out = NULL;
	res->prev = room->prev;
	res->next = room->next;
	res->parent = room;
	return (res);
}

void	ft_init_duplicates(t_room **room, t_link **linkout, t_link **linkin)
{
	(*room)->in = ft_roomcpy(*room);
	(*room)->out = ft_roomcpy(*room);
	(*room)->in->induplicate = true;
	(*room)->out->outduplicate = true;
	*linkout = (*room)->out->link;
	*linkin = (*room)->in->link;
}
