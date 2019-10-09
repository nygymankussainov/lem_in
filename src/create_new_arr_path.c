/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 14:52:29 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/09 13:27:10 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	reindex_paths(t_path *path)
{
	t_queue	*list;

	list = path->list;
	while (list)
	{
		list->room->path = !list->room->status ? path->index : list->room->path;
		list = list->next;
	}
}

void	add_path_list(t_path *path, t_link *link, t_queue **last, int i)
{
	if (!link->room->visited && !link->lock && link->go)
	{
		enqueue(&path->list, link->room, last);
		if (link->room->status == 'e')
			path->endlist = *last;
		path->steps++;
		path->index = i;
	}
}

int		add_list_in_queue(t_queue **queue, t_link *link,
	t_queue **last, t_room *room)
{
	if (!link->room->visited && !link->lock && link->go)
	{
		if (!link->room->status)
			enqueue(queue, link->room, last);
		room->visited = room->status != 'e' ? 1 : room->visited;
		return (1);
	}
	return (0);
}

void	create_list_of_paths(t_room *room, t_path *path, int i)
{
	t_link	*link;
	t_queue	*queue;
	t_queue	*last1;
	t_queue	*last2;

	queue = NULL;
	last1 = NULL;
	last2 = NULL;
	enqueue(&queue, room, &last1);
	enqueue(&path->list, room, &last2);
	while (queue)
	{
		link = room->link;
		while (link)
		{
			add_path_list(path, link, &last2, i);
			if (add_list_in_queue(&queue, link, &last1, room))
				break ;
			link = link->next;
		}
		dequeue(&queue);
		room = queue ? queue->room : room;
	}
}

t_path	*create_new_arr_path(t_farm *farm, int size)
{
	t_path	*new;
	t_link	*link;
	int		i;

	link = NULL;
	if (!(new = (t_path *)ft_memalloc(sizeof(t_path) * size)))
		exit(0);
	i = 0;
	unvisit_rooms(farm, 0);
	while (i < size)
	{
		if (farm->onestep_path && i == 0)
		{
			new[i++].list = farm->onestep_path;
			link = get_start_end_link(farm->onestep_path);
		}
		create_list_of_paths(farm->startroom, &new[i], i);
		i++;
	}
	if (link)
	{
		link->next = farm->onestep_path->room->link;
		farm->onestep_path->room->link = link;
	}
	return (new);
}
