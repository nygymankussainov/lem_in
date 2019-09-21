/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_graph.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:44:48 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/21 16:13:49 by hfrankly         ###   ########.fr       */
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
		if (link->lock == 1 && (*room)->pathpart == link->room->pathpart)
			break ;
		link = link->next;
	}
	(*linkroom) = link->room;
}

// void	ft_link_refresh(t_room *room, t_room *linkroom, t_link *link)
// {
// 	t_link	*tmplink;

// 	if (linkroom == room->parent->out)
// 		ft_change_vars(&room, &linkroom);
// 	ft_connect_with_parent(linkroom, room);
// 	tmplink = room->parent->link;
// 	while (ft_strcmp(tmplink->room->name, linkroom->name))
// 		tmplink = tmplink->next;
// 	tmplink->room = linkroom;
// 	if (linkroom->prev && !ft_strcmp(linkroom->prev->name, room->name))
// 		tmplink->lock = true;
// 	else
// 		tmplink->lock = false;
// 	if (ft_if_destroy(room, linkroom) && room->outduplicate && linkroom->induplicate)
// 	{
// 		tmplink->destroy = true;
// 		tmplink->lock = false;
// 	}
// }

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

t_room	*ft_room_refresh(t_room *room)
{
	t_link	*link;
	t_room	*res;
	
	link = room->link;
	while (link)
	{
		// ft_clean_out_links(link->room);
		ft_link_refresh(room, link->room, link);
		link = link->next;
	}
	res = room->parent;
	// ft_free_room(&room->parent->out);
	// ft_free_room(&room);
	return (res);
}

void	ft_refresh_graph(t_farm *farm)
{
	t_room	*room;
	t_room	**queue;
	t_link	*link;
	int		endqueue;
	int		iter;

	if (!(queue = (t_room**)malloc(sizeof(t_room*) * (farm->room_count + farm->duplicate_count))))
		exit(0);
	iter = 0;
	endqueue = 1;
	queue[iter] = farm->startroom;
	while (queue[iter])
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
