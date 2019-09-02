/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 15:10:05 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/02 16:46:55 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	ft_make_room_inf(t_farm *farm)
{
	t_hashcodes	*hc;
	t_hash_tab	*ht;
	t_link		*link;
	t_room		*room;

	hc = farm->hashcodes;
	ht = farm->h_tab;
	while (hc)
	{
		room = ht[hc->hash_code].room;
		while (room)
		{
			room->pathlength = 2147483637;
			link = room->link;
			while (link)
			{
				link->weight = 1;
				link = link->next;
			}
			room->was = 0;
			room = room->next;
		}
		hc = hc->next;
	}
	ht[farm->start].room->pathlength = 0;
}

void	ft_bell_ford(t_farm *farm)
{
	t_hashcodes	*hc;
	t_hash_tab	*ht;
	t_link		*link;
	t_room		*room;
	int			iter;
	bool		changes;

	iter = -1;
	hc = farm->hashcodes;
	ht = farm->h_tab;
	ft_make_room_inf(farm);
	while (++iter < farm->room_count)
	{
		changes = false;
		hc = farm->hashcodes;
		while (hc)
		{
			room = ht[hc->hash_code].room;
			while (room)
			{
				link = room->link;
				while (link)
				{
					if (link->room->pathlength > room->pathlength + link->weight)
					{
						link->room->pathlength = room->pathlength + link->weight;
						changes = true;
					}
					link = link->next;
				}
				room = room->next;
			}
			hc = hc->next;
		}
		if (!changes)
			break;
	}
}

void	ft_reload_was(t_farm *farm)
{
	t_hash_tab	*ht;
	t_hashcodes	*hc;
	t_room		*room;

	ht = farm->h_tab;
	hc = farm->hashcodes;
	while (hc)
	{
		room = ht[hc->hash_code].room;
		while (room)
		{
			room->was = false;
			room = room->next;
		}
		hc = hc->next;
	}
}

void	ft_show_pathlengthes(t_farm *farm)
{
	t_hashcodes	*hc;
	t_hash_tab	*ht;
	t_room		*room;
	int			iter;

	iter = 0;
	hc = farm->hashcodes;
	ht = farm->h_tab;
	while (hc)
	{
		room = ht[hc->hash_code].room;
		while (room)
		{
			printf("Room name: %-5s   pathlength: %d\n", room->name, room->pathlength);
			room = room->next;
		}
		hc = hc->next;
	}
}

void    lem_in(t_farm *farm)
{
	int i;

	i = 0;
	while (i < 1000000) // проверка скорости
	{
    	ft_bell_ford(farm);
		i++;
	}
	ft_show_pathlengthes(farm);
}
