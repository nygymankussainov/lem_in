/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 15:10:05 by hfrankly          #+#    #+#             */
/*   Updated: 2019/08/29 17:26:46 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_bfslevel_print(t_farm *farm)
{
	t_hash_tab	*ht;
	t_hashcodes *hc;

	ht = farm->h_tab;
	hc = farm->hashcodes;
	while (hc)
	{
		ft_printf("%s = %d", ht[hc->hash_code].room->name, ht[hc->hash_code].room->bfs_lvl);
		hc = hc->next;
	}
}

void	ft_qprint(t_queue *q)
{
	t_qelem		*qe;

	qe = q->begin;
	while (qe)
	{
		ft_putendl(qe->room->name);
		qe = qe->next;
	}
	ft_putchar('\n');
}

void	ft_qinit(t_queue *q)
{
	if (!(q = (t_queue*)malloc(sizeof(t_queue))))
		exit(0);
	q->begin = NULL;
	q->end = NULL;
}

void	ft_qinsert(t_queue *q, t_room *room)
{
	t_qelem		qe;
	t_qelem		*prev;

	qe.room = room;
	qe.next = NULL;
	if (q->end == NULL && q->begin == NULL)
	{
		q->end = &qe;
		q->begin = &qe;
	}
	else
	{
		prev = q->end;
		q->end = &qe;
		prev->next = q->end;
	}
}

t_room	*ft_qget(t_queue *q)
{
	t_room		*room;
	t_qelem		*qe;

	if (ft_isempty(q))
		exit(0);
	room = q->begin->room;
	if (q->begin->next != NULL)
	{
		qe = q->begin->next;
		q->begin->next = NULL;
		q->begin = qe;
	}
	else
	{
		q->begin = NULL;
		q->end = NULL;
	}
	return (room);
}

int		ft_isempty(t_queue *q)
{
	if (q->begin == NULL && q->end == NULL)
		return (1);
	else
		return (0);
}

void	ft_bfs(t_farm *farm)
{
	t_queue		*q;
	t_room		*room;
	t_link		*link;
	int			bfs_lvl;

	ft_qinit(q);
	ft_qinsert(q, farm->h_tab[farm->start].room);
	bfs_lvl = 0;
	while (!ft_isempty(q))
	{
		room = ft_qget(q);
		link = room->link;
		while (link)
		{
			if (bfs_lvl > link->room->bfs_lvl)
				bfs_lvl = link->room->bfs_lvl;
			link = link->next;
		}
		room->bfs_lvl = bfs_lvl;
		link = room->link;
		while (link && link->room->bfs_lvl == 0)
		{
			ft_qinsert(q, link->room);
			link = link->next;
		}
	}
}

void    lem_in(t_farm *farm)
{
    ft_bfs(farm);
}
