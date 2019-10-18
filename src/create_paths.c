/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 14:47:38 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/18 13:28:26 by vhazelnu         ###   ########.fr       */
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
** In fill_struct() function we creating a linked list
** of a new found path
*/

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
			if (end && end->dup && end->out)
				path[size]->steps -=
					enqueue_to_begin(&path[size]->list, end->inroom);
			else
				path[size]->steps -=
					enqueue_to_begin(&path[size]->list, end);
			if (end->status == 'e')
				(*path)->endlist = (*path)->list;
			end = end->prev;
			path[size]->steps++;
		}
	}
}

/*
** Function get_start_end_link() returns a link between
** start and end rooms if such path exists.
*/

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
	return (tmp);
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
	fill_struct(farm, &new, 1);
	delete_dup_rooms(*path);
	while (i < (*path)->size)
	{
		manage_direction(*path + i, 0);
		i++;
	}
	lock_intersecting_links(new);
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
		(*path)->size = 1;
		fill_struct(farm, path, (*path)->size);
		delete_dup_rooms(*path);
		if ((*path)->steps == 1)
			farm->onestep_path = (*path)->list;
		manage_direction(*path, 0);
		(*path)->lines = farm->ants + (*path)->steps - 1;
		if (farm->max_paths == 1 || farm->ants == 1)
			return (0);
		return (1);
	}
	else
		return (create_many_paths(farm, path));
	return (1);
}
