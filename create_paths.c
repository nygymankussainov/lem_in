/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 20:11:22 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/28 18:32:51 by vhazelnu         ###   ########.fr       */
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

int		is_enough_paths(t_path *path, int ants, int i)
{
	while (--i)
		path++;
	if (ants < (*path).steps)
		return (0);
	return (1);
}

int		create_paths(t_farm *farm, t_path **path)
{
	t_queue	*queue;
	t_queue	*last;
	t_path	*new;
	int		i;

	queue = NULL;
	last = NULL;
	i = 1;
	if (!*path)
	{
		if (!(*path = (t_path *)ft_memalloc(sizeof(t_path) * i)))
			exit(0);
	}
	else
	{
		i = count_paths(queue, farm->startroom, last, farm);
		if (!(new = (t_path *)ft_memalloc(sizeof(t_path) * i)))
			exit(0);
		new->next = *path;
		*path = new;
	}
	unvisit_rooms(farm, 0);
	count_steps(queue, farm->startroom, last, *path);
	unvisit_rooms(farm, 0);
	reindex_paths(queue, farm->startroom, *path);
	sort_arr_path(*path, i);
	unvisit_rooms(farm, 0);
	create_queue_of_paths(queue, *path, farm->startroom, i);
	unvisit_rooms(farm, 2);
	if (!is_enough_paths(*path, farm->ants, i))
	{
		if (free_paths(path, i))
			farm->path_nb = i;
		return (0);
	}
	farm->path_nb = i;
	return (1);
}
