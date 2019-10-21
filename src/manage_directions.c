/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_directions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:59:19 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/21 13:04:44 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_queue	*from_start_to_end(t_queue *list, int i)
{
	t_link	*link;

	while (list && list->next)
	{
		link = list->room->link;
		while (link && link->room != list->next->room)
			link = link->next;
		link->lock = i;
		list = list->next;
	}
	return (list);
}

void	from_end_to_start(t_queue *list, int i, int w)
{
	t_link	*link;

	while (list && list->room->status != 's')
	{
		link = list->room->link;
		if (list->room->name != list->prev->room->name)
		{
			while (link && link->room != list->prev->room)
				link = link->next;
			link->weight = w;
			link->lock = i;
		}
		list = list->prev;
	}
}

void	manage_direction(t_path *path, int i)
{
	t_queue	*list;

	if (i == -1)
	{
		list = from_start_to_end(path->list, 0);
		from_end_to_start(list, 0, 1);
		return ;
	}
	list = from_start_to_end(path->list, i);
	from_end_to_start(list, !i, -1);
}
