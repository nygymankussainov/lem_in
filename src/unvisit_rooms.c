/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unvisit_rooms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 18:38:35 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/17 14:06:46 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_count_paths(t_farm *farm)
{
	int		start;
	int		end;
	t_link	*link;

	end = 0;
	start = 0;
	link = farm->startroom->link;
	while (link)
	{
		link = link->next;
		start++;
	}
	link = farm->endroom->link;
	while (link)
	{
		end++;
		link = link->next;
	}
	return ((start < end) ? start : end);
}

void	unvisit_rooms(t_farm *farm, int i)
{
	t_hashcodes	*tmp;
	t_room		*room;

	tmp = farm->hashcodes;
	while (tmp)
	{
		room = farm->h_tab[tmp->hash_code].room;
		while (room)
		{
			room->antnbr = i == 2 ? -1 : room->antnbr;
			room->visited = 0;
			if (room->outroom)
			{
				room->outroom->antnbr = i == 2 ? -1 : room->outroom->antnbr;
				room->outroom->visited = 0;
			}
			room = room->next;
		}
		tmp = tmp->next;
	}
}
