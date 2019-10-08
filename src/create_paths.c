/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 14:47:38 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/08 20:17:55 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		free_paths(t_path **path)
{
	t_path	*tmp;
	t_path	*save;
	int		i;

	save = (*path)->next;
	while (*path)
	{
		i = 0;
		if (*path == save)
		{
			*path = (*path)->next;
			if (!*path)
				break ;
		}
		tmp = (*path)->next;
		while (i < (*path)->size)
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
		path[size]->steps--;
		while (end)
		{
			enqueue_to_begin(&path[size]->list, end);
			if (end->status == 'e')
				(*path)->endlist = (*path)->list;
			end = end->prev;
			path[size]->steps++;
		}
	}
}

t_link	*get_start_end_link(t_queue *list)
{
	t_link	*link;
	t_link	*prev;
	t_link	*tmp;

	link = list->room->link;
	tmp = NULL;
	if (link && link->room == list->next->room)
	{
		tmp = link;
		list->room->link = list->room->link->next;
	}
	else
	{
		while (link)
		{
			prev = link;
			if (link->next && link->next->room == list->next->room)
			{
				tmp = link->next;
				prev->next = tmp->next;
				break ;
			}
			link = link->next;
		}
	}
	return (tmp);
}

int		create_many_paths(t_farm *farm, t_path **path)
{
	int		size;
	t_path	*new;
	int		i;
	t_link	*link;

	size = (*path)->size + 1;
	link = NULL;
	if (!(new = (t_path *)ft_memalloc(sizeof(t_path) * size)))
		exit(0);
	i = 0;
	unvisit_rooms(farm, 0);
	while (i < size)
	{
		if (farm->onestep_path && i == 0)
		{
			new[i].list = farm->onestep_path;
			link = get_start_end_link(farm->onestep_path);
			i++;
		}
		create_list_of_paths(farm->startroom, &new[i], i);
		i++;
	}
	if (link)
	{
		link->next = farm->onestep_path->room->link;
		farm->onestep_path->room->link = link;
	}
	new->size = size;
	new->next = *path;
	*path = new;
	sort_paths(*path, i);
	unvisit_rooms(farm, 0);
	i = 0;
	while (i < size)
		reindex_paths(*path + i++);
	sort_arr_path(*path, size);
	(*path)->size = size;
	if (!is_need_more_paths(farm->ants, path, farm->size) ||
		(*path)->size >= farm->max_paths)
		return (0);
	return (1);
}

int		create_paths(t_farm *farm, t_path **path)
{
	t_path	*new;
	int		i;

	i = 0;
	if (*path)
		delete_dup_rooms(*path);
	if (!*path)
	{
		if (!(*path = (t_path *)ft_memalloc(sizeof(t_path))))
			exit(0);
		(*path)->size = 1;
		fill_struct(farm, path, (*path)->size);
		if ((*path)->steps == 1)
			farm->onestep_path = (*path)->list;
		manage_direction(*path, 0); /* make path directed from start room to end room */
		(*path)->lines = farm->ants + (*path)->steps - 1;
		if (farm->max_paths == 1 || farm->ants == 1)
			return (0);
		return (1);
	}
	else
	{
		if (!(new = (t_path *)ft_memalloc(sizeof(t_path))))
			exit(0);
		new->size = 1;
		fill_struct(farm, &new, new->size);
		make_path_directed(new); /* make new path directed from start room to end room */
		while (i < (*path)->size)
		{
			manage_direction(*path + i, 0); /* make old path(s) directed from start room to end room */
			i++;
		}
		find_disjoint_paths(path);
		find_disjoint_paths(&new);
		free_paths(&new);
		return (create_many_paths(farm, path));
	}
	return (1);
}
