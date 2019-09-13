/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpful_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:06:19 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/12 20:33:49 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_links(t_hashcodes *hashcodes, t_hash_tab *h_tab)
{
	t_link		*tmp;
	t_hashcodes	*tmp1;
	t_room		*tmp2;

	while (hashcodes)
	{
		tmp1 = hashcodes->next;
		while (h_tab[hashcodes->hash_code].room)
		{
			tmp2 = h_tab[hashcodes->hash_code].room->next;
			while (h_tab[hashcodes->hash_code].room->link)
			{
				tmp = h_tab[hashcodes->hash_code].room->link->next;
				printf("%s-%s\n", h_tab[hashcodes->hash_code].room->name,
					h_tab[hashcodes->hash_code].room->link->room->name);
				h_tab[hashcodes->hash_code].room->link = tmp;
			}
			h_tab[hashcodes->hash_code].room = tmp2;
		}
		hashcodes = tmp1;
	}
}

t_room	*find_startend(t_room *room, char c)
{
	while (room)
	{
		if (room->status == c)
		{
			room->visited = c == 's' ? 1 : room->visited;
			return (room);
		}
		room = room->next;
	}
	return (NULL);
}

int		is_room_exist(int hash, t_hashcodes *hashcodes)
{
	while (hashcodes)
	{
		if (hash == hashcodes->hash_code)
			return (1);
		hashcodes = hashcodes->next;
	}
	return (0);
}

void	ft_show_pathlengthes(t_farm *farm)
{
	t_hashcodes	*hc;
	t_hash_tab	*ht;
	t_room		*room;
	t_link		*link;
	int			iter;

	iter = 0;
	hc = farm->hashcodes;
	ht = farm->h_tab;
	while (hc)
	{
		room = ht[hc->hash_code].room;
		while (room)
		{
			if (room->in)
			{
				printf("%-10s %-5s  pathlength: %d\n", "Room in:", room->name, room->in->pathlength);
				printf("%-10s %-5s  pathlength: %d\n", "Room out:", room->name, room->out->pathlength);
			}
			else
				printf("%-10s %-5s  pathlength: %d\n", "Room:", room->name, room->pathlength);
			link = room->link;
			// while (link)
			// {
			// 	ft_printf("Source: %-5s Destination: %-5s Link weight: %d\n", room->name, link->room->name, link->weight);
			// 	link = link->next;
			// }
			room = room->next;
		}
		hc = hc->next;
	}
}
