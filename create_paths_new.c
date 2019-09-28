/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_paths_new.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 14:47:38 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/28 18:43:10 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		free_paths(t_path **path, int size)
{
	t_path	*tmp;
	t_path	*save;
	int		i;

	// if (!(*path)->next)
	// 	return (1);
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
		path[size]->steps--;
		while (end)
		{
			enqueue_to_begin(&path[size]->list, end);
			end = end->prev;
			path[size]->steps++;
		}
	}
}

int		create_many_paths(t_farm *farm, t_path **path)
{
	int		size;
	t_path	*new;
	int		i;

	size = count_paths(NULL, farm->startroom, NULL, farm);
	if (!(new = (t_path *)ft_memalloc(sizeof(t_path) * size)))
		exit(0);
	i = 0;
	unvisit_rooms(farm, 0);
	while (i < size)
	{
		create_list_of_paths(farm->startroom, &new[i], i);
		i++;
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
	//check if enough paths
	return (1);
}

int		create_paths(t_farm *farm, t_path **path)
{
	t_path	*new;
	int		i;
	int		ret;

	ret = 1;
	i = 0;
	if (!*path)
	{
		if (!(*path = (t_path *)ft_memalloc(sizeof(t_path))))
			exit(0);
		(*path)->size = 1;
		fill_struct(farm, path, (*path)->size);
		manage_direction(*path, 0);
		printf("AFTER CREATE_PATH\n");
		print_graph(farm);
		print_list(*path);
	}
	else
	{
		if (!(new = (t_path *)ft_memalloc(sizeof(t_path))))
			exit(0);
		new->size = 1;
		fill_struct(farm, &new, new->size);
		make_path_directed(new);
		while (i < (*path)->size)
		{
			manage_direction(path[i], 0);
			i++;
		}
		find_disjoint_paths(path);
		find_disjoint_paths(&new);
		free_paths(&new, new->size);
		ret = create_many_paths(farm, path);
		printf("AFTER CREATE MANY PATHS\n");
		print_graph(farm);
		print_list(*path);
	}
	return (ret);
}
