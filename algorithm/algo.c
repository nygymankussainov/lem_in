/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 15:10:05 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/01 16:03:18 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

// void	ft_bfslevel_print(t_farm *farm)
// {
// 	t_hash_tab	*ht;
// 	t_hashcodes *hc;

// 	ht = farm->h_tab;
// 	hc = farm->hashcodes;
// 	while (hc)
// 	{
// 		ft_printf("%s = %d", ht[hc->hash_code].room->name, ht[hc->hash_code].room->bfs_lvl);
// 		hc = hc->next;
// 	}
// }

// void	ft_qprint(t_queue *q)
// {
// 	t_qelem		*qe;

// 	qe = q->begin;
// 	while (qe)
// 	{
// 		ft_putendl(qe->room->name);
// 		qe = qe->next;
// 	}
// 	ft_putchar('\n');
// }

// void	ft_qinit(t_queue **q)
// {
// 	if (!(*q = (t_queue*)malloc(sizeof(t_queue))))
// 		exit(0);
// 	(*q)->begin = NULL;
// 	(*q)->end = NULL;
// }

// void	ft_qinsert(t_queue *q, t_room *room)
// {
// 	t_qelem		*qe;
// 	t_qelem		*prev;

// 	if (!(qe = (t_qelem*)malloc(sizeof(t_qelem))))
// 		exit(0);
// 	room->was++;
// 	qe->room = room;
// 	qe->next = NULL;
// 	if (q->end == NULL && q->begin == NULL)
// 	{
// 		q->end = qe;
// 		q->begin = qe;
// 	}
// 	else
// 	{
// 		prev = q->end;
// 		q->end = qe;
// 		prev->next = q->end;
// 	}
// }

// int		ft_qisempty(t_queue *q)
// {
// 	if (q->begin == NULL && q->end == NULL)
// 		return (1);
// 	else
// 		return (0);
// }

// t_room	*ft_qget(t_queue *q)
// {
// 	t_room		*room;
// 	t_qelem		*qe;

// 	if (ft_qisempty(q))
// 		exit(0);
// 	room = q->begin->room;
// 	if (q->begin->next != NULL)
// 	{
// 		qe = q->begin->next;
// 		q->begin->next = NULL;
// 		q->begin = qe;
// 	}
// 	else
// 	{
// 		q->begin = NULL;
// 		q->end = NULL;
// 	}
// 	return (room);
// }

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

// void	ft_bell_ford(t_farm *farm)
// {
// 	t_hash_tab	*ht;
// 	t_link		*link;
// 	t_room		*room;
// 	t_queue		*q;
// 	int			iter;
// 	bool		changes;

// 	iter = -1;
// 	ht = farm->h_tab;
// 	ft_make_room_inf(farm);
// 	q = NULL;
// 	ft_qinit(&q);
// 	while (++iter < farm->room_count)
// 	{
// 		changes = false;
// 		ft_qinsert(q, ht[farm->start].room);
// 		while (!ft_qisempty(q))
// 		{
// 			room = ft_qget(q);
// 			link = room->link;
// 			while (link)
// 			{
// 				if (link->room->pathlength > room->pathlength + link->weight)
// 				{
// 					link->room->pathlength = room->pathlength + link->weight;
// 					changes = true;
// 				}
// 				if (link->room->was != iter)
// 					ft_qinsert(q, link->room);
// 				link = link->next;
// 			}
// 		}
// 		if (!changes)
// 			break;
// 	}
// 	free(q);
// }

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
