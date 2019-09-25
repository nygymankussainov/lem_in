/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_graph.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:44:48 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/25 15:40:51 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void	ft_change_vars(t_room **room, t_room **linkroom)
{
	t_link	*link;

	(*room) = (*linkroom);
	link = (*linkroom)->link;
	while (link)
	{
		if (link->lock == 1)
		{
			(*linkroom) = link->room;
			if ((*room)->prev == link->room)
				break ;
		}
		link = link->next;
	}
	if (link)
		(*linkroom) = link->room;
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

void	ft_link_refresh(t_room *room, t_room *linkroom, t_link *link)
{
	t_link	*parentlink;
	t_room	*inputroom;
	
	inputroom = room;
	if (!ft_strcmp(room->name, "Hnf3") || !ft_strcmp(room->name, "Zmn4"))
		ft_putstr("here");
	if (linkroom == room->parent->out)
		ft_change_vars(&room, &linkroom);
	else
		room = room->parent->out;
	ft_change_link(room, &link);
	ft_connect_with_parent(linkroom, room);
	parentlink = room->parent->link;
	while (ft_strcmp(parentlink->room->name, linkroom->name))
		parentlink = parentlink->next;
	parentlink->room = linkroom;
	parentlink->lock = link->lock;
	if (ft_check_destroy_link(room, linkroom))
		parentlink->destroy = true;
	if (ft_if_destroy(room, linkroom) && room->outduplicate && linkroom->induplicate)
	{
		parentlink->destroy = true;
		parentlink->lock = false;
	}
}

void	ft_unwas_link(t_link *link)
{
	while (link)
	{
		link->room->was = false;
		if (link->room->in)
		{
			link->room->in->was = false;
			link->room->out->was = false;
		}
		link = link->next;
	}
}

t_room	*ft_room_refresh(t_room *room)
{
	t_link	*link;
	t_room	*res;
	
	link = room->link;
	ft_unwas_link(link);
	while (link && link->room->was == false)
	{
		ft_link_refresh(room, link->room, link);
		link->room->was = true;
		if (link->room->in)
		{
			link->room->in->was = true;
			link->room->out->was = true;
		}
		link = link->next;
	}
	res = room->parent;
	return (res);
}

void	ft_refresh_graph(t_farm *farm)
{
	t_room	*room;
	t_room	**queue;
	t_link	*link;
	int		endqueue;
	int		iter;

	if (!(queue = (t_room**)malloc(sizeof(t_room*) * (farm->room_count + farm->duplicate_count) * 2)))
		exit(0);
	iter = 0;
	endqueue = 1;
	queue[iter] = farm->startroom;
	while (iter < endqueue)
	{
		room = queue[iter];
		if (room->induplicate)
			room = ft_room_refresh(room);
		link = room->link;
		while (link)
		{
			if (link->room->visited == false && link->room->status != 's' && link->room->outduplicate == false)
			{
				queue[endqueue++] = link->room;
				link->room->visited = true;
				if (link->room->induplicate)
				{
					link->room->parent->visited = true;
					link->room->parent->out->visited = true;
				}
			}
			link = link->next;
		}
		iter++;
	}
	free(queue);
}
