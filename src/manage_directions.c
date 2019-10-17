/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_directions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:59:19 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/17 14:06:07 by vhazelnu         ###   ########.fr       */
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
		link->go = 1;
		list = list->next;
	}
	return (list);
}

void	from_end_to_start(t_queue *list, int i)
{
	t_link	*link;

	while (list && list->room->status != 's')
	{
		link = list->room->link;
		if (list->room->name != list->prev->room->name)
		{
			while (link && link->room != list->prev->room)
				link = link->next;
			link->weight = -1;
			link->go = 1;
			link->lock = i;
		}
		list = list->prev;
	}
}

void	manage_direction(t_path *path, int i)
{
	t_queue	*list;

	list = from_start_to_end(path->list, i);
	from_end_to_start(list, !i);
}
