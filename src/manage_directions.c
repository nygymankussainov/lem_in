/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_directions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:59:19 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/08 20:12:04 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	make_path_directed(t_path *path)
{
	t_link	*link;
	t_queue	*list;

	list = path->list;
	while (list && list->next)
	{
		link = list->room->link;
		while (link && link->room != list->next->room)
			link = link->next;
		link->lock = 0;
		link->go = 1;
		if (!list->next)
			break ;
		list = list->next;
	}
}

void	manage_direction(t_path *path, int i)
{
	t_link	*link;
	t_queue	*list;

	list = path->list;
	while (list && list->next)
	{
		link = list->room->link;
		while (link && link->room != list->next->room)
			link = link->next;
		link->lock = i;
		link->go = 1;
		if (!list->next)
			break ;
		list = list->next;
	}
	while (list && list->room->status != 's')
	{
		link = list->room->link;
		if (list->room->name != list->prev->room->name)
		{
			while (link && link->room != list->prev->room)
				link = link->next;
			link->weight = -1;
			link->go = 1;
			link->lock = link->lock != i ? i : !i;
		}
		list = list->prev;
	}
}
