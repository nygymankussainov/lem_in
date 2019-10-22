/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_arr_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:35:14 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/22 14:07:16 by vhazelnu         ###   ########.fr       */
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

void	add_room_in_list(t_path *path, t_room *room, t_queue **last, int i)
{
	enqueue(&path->list, room, last);
	if (room->status == 'e')
		path->endlist = *last;
	path->steps += room->status == 's' ? 0 : 1;
	path->index = i;
}

t_queue	*get_unvisited_room(t_queue *list)
{
	while (list)
	{
		if (!list->room->visited)
		{
			if (list->room->status == 'e')
				list->room->visited = 1;
			break ;
		}
		list = list->next;
	}
	return (list);
}

void	write_rooms_in_list(t_path *new, t_farm *farm)
{
	t_room	*room;
	t_queue	*list;
	t_queue	*last;
	int		i;

	room = farm->startroom;
	list = room->linkwith;
	i = 0;
	while (list)
	{
		last = NULL;
		add_room_in_list(&new[i], room, &last, i);
		while (list && room->status != 'e')
		{
			add_room_in_list(&new[i], list->room, &last, i);
			room = list->room;
			room->visited = !room->status ? 1 : room->visited;
			list = room->linkwith;
		}
		room = farm->startroom;
		list = get_unvisited_room(room->linkwith);
		i++;
	}
}

t_path	*create_new_arr_path(t_farm *farm, int size)
{
	t_path	*new;

	if (!(new = (t_path *)ft_memalloc(sizeof(t_path) * size)))
		exit(0);
	unvisit_rooms(farm, 0);
	write_rooms_in_list(new, farm);
	return (new);
}
