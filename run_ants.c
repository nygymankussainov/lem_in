/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ants.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 17:57:58 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/05 19:14:42 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_lock(t_room *room, t_link *link)
{
	t_room	*room_tmp;
	t_link	*link_tmp;

	room_tmp = link->room;
	link_tmp = room_tmp->link;
	if (!link->lock)
		return (0);
	if (!room->dup)
	{
		while (link_tmp && link_tmp->room != room)
			link_tmp = link_tmp->next;
		if (room_tmp->dup && room_tmp->in && !room->dup)
			link_tmp = room_tmp->outroom->link;
	}
	else if (room->dup && room->out)
		while (link_tmp && link_tmp->room->name != room->name)
			link_tmp = link_tmp->next;
	if (link_tmp && !link_tmp->lock)
		return (1);
	return (0);
}

void	unlock_links(t_farm *farm)
{
	t_hashcodes	*tmp;
	t_room		*room;
	t_link		*link;
	int			key;

	tmp = farm->hashcodes;
	key = 0;
	while (tmp)
	{
		room = farm->h_tab[tmp->hash_code].room;
		while (room)
		{
			link = room->link;
			while (link)
			{
				link->lock = 0;
				link = link->next;
				if (!link && room->dup && !key)
				{
					if (room->in)
						link = room->outroom->link;
					else if (room->out)
						link = room->inroom->link;
					key = 1;
				}
			}
			key = 0;
			room = room->next;
		}
		tmp = tmp->next;
	}
}

void	run(t_queue *queue, t_room *room, t_queue *last)
{
	t_link	*link;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (queue)
	{
		link = room->link;
		while (link)
		{
			if (room->outroom && room->outroom == link->room)
			{
				enqueue(&queue, link->room, &last);
				link->room->visited = 1;
				link = link->next;
				continue ;
			}
			if (!link->room->visited && check_lock(room, link))
			{
				enqueue(&queue, link->room, &last);
				link->room->visited = link->room-> status != 'e' ? 1 : link->room->visited;
				printf("L%d-%s", j, link->room->name);
				i += room->status == 's' ? 1 : 0;
				j++;
				if (j < i || (room->status == 's' && link->next))
					printf(" ");
			}
			link = link->next;
		}
		dequeue(&queue);
		room = queue ? queue->room : room;
		if (j >= i)
		{
			j = 0;
			printf("\n");
		}
	}
}

void	check_link(t_room *room1, t_room *room2, t_path *path)
{
	t_path	*tmp;
	t_link	*link;

	tmp = path;
	while (tmp)
	{
		if (tmp->room == room2 && tmp->room->next == room1)
		{
			link = room2->link;
			while (link)
			{
				if (link->room->name == room1->name)
					link->lock = 1;
				link = link->next;
			}
			link = room1->link;
			while (link)
			{
				if (link->room->name == room2->name)
					link->lock = 1;
				link = link->next;
			}
		}
		tmp = tmp->next;	
	}
}

void	run_ants(t_farm *farm)
{
	t_room	*room1;
	t_room	*room2;
	t_path	*path;
	int		i;

	i = 0;
	unvisit_rooms(farm);
	unlock_links(farm);
	i = 0;
	while (farm->paths[i + 1])
	{
		path = farm->paths[i];
		path->room = path->next->room;
		while (path->room)
		{
			room1 = path->room;
			room2 = path->next->room;
			while (room1->name == room2->name)
				room2 = path->next->room;
			check_link(room1, room2, farm->paths[i + 1]);
			path->room = path->room->next;
		}
		i++;
	}
}
