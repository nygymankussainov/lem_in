/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_directions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:59:19 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/27 18:39:33 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	make_path_directed(t_path *path)
{
	t_link	*link;
	t_queue	*list;

	list = path->list;
	while (list)
	{
		link = list->room->link;
		while (link && link->room != list->next->room)
			link = link->next;
		link->lock = 0;
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
	while (list)
	{
		link = list->room->link;
		while (link && link->room != list->next->room)
			link = link->next;
		link->lock = i;
		if (!list->next)
			break ;
		list = list->next;
	}
	while (list)
	{
		link = list->room->link;
		while (link && link->room != list->prevroom)
			link = link->next;
		link->weight = -1;
		link->lock = link->lock != i ? i : !i;
		list = list->next;
	}
}
