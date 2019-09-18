/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 21:27:11 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/17 18:37:00 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_connect_in_out(t_link **linkout, t_link **linkin, t_room *room)
{
	(*linkout)->room = room->in;
	(*linkout)->weight = 0;
	(*linkout)->next = NULL;
	(*linkin)->room = room->out;
	(*linkin)->lock = 1;
	(*linkin)->weight = 0;
	(*linkin)->next = NULL;
}

void	ft_create_out_link_if_nextroom(t_room *out, t_link **linkout,
t_room *linkroom)
{
	t_link	*link;

	(*linkout)->room = linkroom;
	(*linkout)->weight = 1;
	(*linkout)->lock = 1;
	link = linkroom->link;
	while (link->room != out->parent)
		link = link->next;
	link->room = out;
	link->weight = -1;
}

void	ft_create_out_link(t_room *out, t_link **linkout,
t_room *linkroom, t_room *nextroom)
{
	t_link	*link;

	if (linkroom == nextroom)
		ft_create_out_link_if_nextroom(out, linkout, linkroom);
	else
	{
		(*linkout)->room = linkroom;
		(*linkout)->weight = 1;
		link = linkroom->link;
		while (link->next)
			link = link->next;
		if (!(link->next = (t_link*)malloc(sizeof(t_link))))
			exit(0);
		link = link->next;
		link->room = out;
		link->lock = 1;
	}
	if (!((*linkout)->next = (t_link*)malloc(sizeof(t_link))))
		exit(0);
	(*linkout) = (*linkout)->next;
}

void	ft_create_in_link(t_room *in, t_link **linkin,
t_room *linkroom, t_room *nextroom)
{
	t_link	*link;

	nextroom = (void*)nextroom;
	(*linkin)->room = linkroom;
	if (linkroom == in->parent->prev)
	{
		(*linkin)->lock = 0;
		(*linkin)->weight = -1;
	}
	else
		(*linkin)->lock = 1;
	link = linkroom->link;
	while (link->room != in->parent)
		link = link->next;
	link->room = in;
	link->weight = 1;
	if (!((*linkin)->next = (t_link*)malloc(sizeof(t_link))))
		exit(0);
	(*linkin) = (*linkin)->next;
}
