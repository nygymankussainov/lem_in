/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_paths_new.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 14:47:38 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/23 20:01:48 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		free_paths(t_path **path, int size)
{
	t_path	*tmp;
	t_path	*save;
	int		i;

	if (!(*path)->next)
		return (1);
	save = (*path)->next;
	i = 0;
	while (*path)
	{
		if (*path == save)
		{
			*path = (*path)->next;
			if (!*path)
				break ;
		}
		tmp = (*path)->next;
		while (i < size)
		{
			while ((*path)[i].list)
				dequeue(&(*path)[i].list);
			i++;
		}
		free(*path);
		*path = tmp;
	}
	*path = save;
	return (0);
}

void	fill_struct(t_farm *farm, t_path **path, int size)
{
	t_room	*end;
	t_queue	*last;

	while (size--)
	{
		end = farm->endroom;
		last = NULL;
		while (end)
		{
			enqueue(&path[size]->list, end, &last, 1);
			end = end->prev;
			path[size]->steps++;
		}
	}
}

int		create_many_paths(t_farm *farm, t_path **path, int size)
{
	t_queue	*queue;
	t_queue	*last;

	queue = NULL;
	last = NULL;
	unvisit_rooms(farm, 0);
	count_steps(queue, farm->startroom, last, *path);
	sort_paths(*path, size);
	unvisit_rooms(farm, 0);
	reindex_paths(queue, farm->startroom, *path);
	sort_arr_path(*path, size);
	unvisit_rooms(farm, 0);
	create_queue_of_paths(queue, *path, farm->startroom, size);
	unvisit_rooms(farm, 2);
	if (farm->ants < expression(*path, size))
	{
		if (free_paths(path, size))
			farm->path_nb = size;
		return (0);
	}
	farm->path_nb = size;
	return (1);
}

void	inverse_edges(t_room *end)
{
	t_room	*prev;
	t_link	*link;

	while (end && end->status != 's')
	{
		end = end->outroom ? end->outroom : end;
		link = end->link;
		while (link && link->room->name != end->prev->name)
			link = link->next;
		link->weight = -1;
		prev = end->prev;
		link = prev->link;
		while (link && link->room->name != end->name)
			link = link->next;
		link->lock = 1;
		end = end->prev;
	}
}

int		create_paths(t_farm *farm, t_path **path)
{
	t_path	*new;
	t_queue	*queue;
	t_queue	*last;
	int		size;

	queue = NULL;
	last = NULL;
	inverse_edges(farm->endroom);
	if (!*path)
	{
		if (!(*path = (t_path *)ft_memalloc(sizeof(t_path) * 1)))
			exit(0);
		fill_struct(farm, path, 1);
		(*path)->size = 1;
		return (1);
	}
	else
	{
		size = count_paths(queue, farm->startroom, last, farm);
		if (!(new = (t_path *)ft_memalloc(sizeof(t_path) * (*path)->size)))
			exit(0);
		new->size = size;
		new->next = *path;
		*path = new;
	}
	return (create_many_paths(farm, path, (*path)->size));
}
