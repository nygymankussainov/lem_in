/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 18:14:39 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/28 11:20:52 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

bool	ft_check_destroy_link(t_room *room1, t_room *room2)
{
	t_link	*link;

	link = room2->link;
	while (link && ft_strcmp(link->room->name, room1->name))
		link = link->next;
	if (link && link->destroy == true)
		return (true);
	return (false);
}

void	ft_clean_out_links(t_room *room)
{
	t_link	*link;
	t_link	*tmplink;

	link = room->link;
	while (link)
	{
		if (link->room->outduplicate)
		{
			tmplink = link->next;
			free(link);
			link = tmplink;
		}
		else
			link = link->next;		
	}
}

void	ft_change_link(t_room *room, t_link **link)
{
	t_link	*reslink;

	reslink = room->link;
	while(reslink && reslink->room != (*link)->room)
		reslink = reslink->next;
	if (reslink == NULL)
		return ;
	*link = reslink;
}

t_link	*ft_change_parent_link(t_room *room, t_room *linkroom, t_link *link)
{
	t_link	*parentlink;

	parentlink = room->parent->link;
	while (ft_strcmp(parentlink->room->name, linkroom->name))
		parentlink = parentlink->next;
    parentlink->room = linkroom;
	parentlink->lock = link->lock;
	return (parentlink);
}

void	ft_link_refresh(t_room *room, t_room *linkroom, t_link *link)
{
	t_link	*parentlink;
	
	if (linkroom == room->parent->out)
		ft_change_vars(&room, &linkroom);
	else
		room = room->parent->out;
	ft_change_link(room, &link);
	ft_connect_with_parent(linkroom, room);
	parentlink = ft_change_parent_link(room, linkroom, link);
	if (ft_check_destroy_link(room, linkroom))
		parentlink->destroy = true;
	if (ft_if_destroy(room, linkroom) && room->outduplicate && linkroom->induplicate && link->lock == true)
	{
		parentlink->destroy = true;
		parentlink->lock = false;
	}
}
