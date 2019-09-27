/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_disjoint_paths.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 18:57:15 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/27 19:16:22 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_link(t_queue *list)
{
	t_link	*link;
	int		lock1;

	link = list->room->link;
	while (link && link->room != list->next->room)
		link = link->next;
	if (!(lock1 = link->lock))
		return (0);
	link = list->next->room->link;
	while (link && link->room != list->room)
		link = link->next;
	if (!lock1 && !link->lock)
	{
		link->lock = 1;
		return (1);
	}
	return (0);
}

void	find_disjoint_paths(t_path **path)
{
	t_link	*link;
	t_queue	*list;
	int		i;

	i = 0;
	while (i < (*path)->size)
	{
		list = path[i]->list;
		while (list)
		{
			if (check_link(list))
				list->room->link->lock = 1;
			list = list->next;
		}
		i++;
	}
}
