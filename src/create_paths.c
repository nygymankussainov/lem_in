/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 14:47:38 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/21 22:32:43 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_path(t_path *path)
{
	while (path->list)
		dequeue(&path->list);
	free(path);
	path = NULL;
}

/*
** In get_new_path() function we creating a linked list
** of a new found path.
*/

int		get_new_path(t_farm *farm, t_path **path, t_path *old)
{
	t_room	*end;
	t_queue	*last;

	end = farm->endroom;
	last = NULL;
	(*path)->steps--;
	while (end)
	{
		if ((*path)->steps > 1000)
		{
			delete_dup_rooms(old);
			free_path(*path);
			return (0);
		}
		if (end && end->dup && end->out)
			enqueue_to_begin(&(*path)->list, end->inroom);
		else
			enqueue_to_begin(&(*path)->list, end);
		if (end->status == 'e')
			(*path)->endlist = (*path)->list;
		end = end->prev;
		(*path)->steps++;
	}
	return (1);
}

/*
** Here in create_paths() and create_many_paths() functions
** we make edges in paths directed from start to end
*/

int		create_many_paths(t_farm *farm, t_path **path)
{
	t_path	*new;
	int		i;

	i = 0;
	if (!(new = (t_path *)ft_memalloc(sizeof(t_path))))
		exit(0);
	if (!get_new_path(farm, &new, *path))
		return (0);
	delete_dup_rooms(*path);
	while (i < (*path)->size)
	{
		manage_direction(*path + i, -1);
		i++;
	}
	fill_room_linkwith(new);
	free_path(new);
	new = create_new_arr_path(farm, (*path)->size + 1);
	new->size = (*path)->size + 1;
	new->next = *path;
	*path = new;
	return (sort_paths(farm, path, (*path)->size));
}

int		create_paths(t_farm *farm, t_path **path)
{
	if (!*path)
	{
		if (!(*path = (t_path *)ft_memalloc(sizeof(t_path))))
			exit(0);
		get_new_path(farm, path, *path);
		(*path)->size = 1;
		fill_room_linkwith(*path);
		delete_dup_rooms(*path);
		manage_direction(*path, 0);
		if (farm->max_paths == 1 || farm->ants == 1)
			return (0);
		return (1);
	}
	else
		return (create_many_paths(farm, path));
	return (1);
}
