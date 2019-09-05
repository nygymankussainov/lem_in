/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 15:10:05 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/05 11:34:20 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

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
			printf("Room: %-5s   pathlength: %d\n", room->name, room->pathlength);
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
			room->was = 0;
			room = room->next;
		}
		hc = hc->next;
	}
	room = ht[farm->start].room;
	while (room)
	{
		if (room->status == 's')
		{
			room->pathlength = 0;
			farm->startroom = room;
			break;
		}
		room = room->next;
	}
}

void	ft_putarray(t_room **room, int begin, int end)
{
	while (begin < end)
	{
		ft_putstr(room[begin]->name);
		ft_putchar('-');
		begin++;
	}
	ft_putchar('\n');
}

void	ft_bell_ford(t_farm *farm)
{
	t_link		*link;
	t_room		*room;
	t_room		**queue;
	int			iter;
	int			endqueue;
	int			i;
	bool		changes;

	i = 0;
	ft_make_room_inf(farm);
	if (!(queue = (t_room**)malloc(sizeof(t_room*) * farm->room_count)))
		exit(0);
	changes = true;
	while (i < farm->room_count && changes == true)
	{
		iter = 0;
		endqueue = 1;
		queue[0] = farm->startroom;
		changes = false;
		while (iter < farm->room_count && iter < endqueue)
		{
			room = queue[iter];
			link = room->link;
			while (link)
			{
				if (!link->lock && link->room->pathlength > room->pathlength + link->weight)
				{
					link->room->pathlength = room->pathlength + link->weight;
					link->room->prev = room;
					queue[endqueue] = link->room;
					changes = true;
					endqueue++;
				}
				link = link->next;
			}
			iter++;
		}
		if (i == farm->room_count - 1 && changes == true)
			exit(0);
		i++;
	}
	free(queue);
}


// void	ft_bell_ford(t_farm *farm)
// {
// 	t_hashcodes	*hc;
// 	t_hash_tab	*ht;
// 	t_link		*link;
// 	t_room		*room;
// 	int			iter;
// 	bool		changes;

// 	iter = -1;
// 	hc = farm->hashcodes;
// 	ht = farm->h_tab;
// 	ft_make_room_inf(farm);
// 	while (++iter < farm->room_count - 1)
// 	{
// 		changes = false;
// 		hc = farm->hashcodes;
// 		while (hc)
// 		{
// 			room = ht[hc->hash_code].room;
// 			while (room)
// 			{
// 				link = room->link;
// 				while (link)
// 				{
// 					if (!link->lock && link->room->pathlength > room->pathlength + link->weight)
// 					{
// 						link->room->pathlength = room->pathlength + link->weight;
// 						changes = true;
// 					}
// 					link = link->next;
// 				}
// 				room = room->next;
// 			}
// 			hc = hc->next;
// 		}
// 		// ft_show_pathlengthes(farm);
// 		// ft_putchar('\n');
// 		if (!changes)
// 			break;
// 	}
// }

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

void    lem_in(t_farm *farm)
{
	int i;

	i = 0;
	while (i < 1) // проверка скорости
	{
    	ft_bell_ford(farm);
		find_shortest_path(farm);
		i++;
	}
	find_shortest_path(farm);
	ft_putchar('\n');
}
