/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 13:23:33 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/22 12:47:42 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_connect_with_parent(t_room *src, t_room *dst)
{
	t_link	*link;

	link = src->link;
	while (link && ft_strcmp(dst->name, link->room->name))
		link = link->next;
	if (link == NULL)
		return ;
	link->room = dst->parent;
}

void	ft_free_room(t_room **room)
{
	t_link	*link;
	t_link	*tmplink;

	link = (*room)->link;
	while (link)
	{
		tmplink = link->next;
		link->next = NULL;
		free(link);
		link = tmplink;
	}
	free(*room);
	*room = NULL;
}
