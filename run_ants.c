/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ant.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 17:57:58 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/12 18:27:23 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		expression(t_path *path, int i)
{
	int		curr;
	int		result;

	curr = i;
	result = 0;
	while (i > 0)
	{
		i--;
		result += path[curr].steps - path[i].steps;
	}
	return (result);
}

int		issend(t_path *path, int ant, int i)
{
	if (ant >= expression(path, i))
		return (1);
	return (0);
}

int		ants_left_in_path(t_path path)
{
	t_queue		*q_path;

	q_path = path.list;
	while (q_path)
	{
		if (q_path->room->antnbr >= 0 && q_path->room->status != 'e')
			return (1);
		q_path = q_path->next;
	}
	return (0);
}

// void	run(t_farm *farm, int size, t_path *path)
// {
// 	int		ant;
// 	int		i;
// 	int		tmp;
// 	int		sp;

// 	ant = 0;
// 	tmp = -1;
// 	sp = 0;
// 	while (ant < farm->ants)
// 	{
// 		i = 0;
// 		while (i < size)
// 		{
// 			if (!issend(path, farm->ants - ant, i))
// 			{
// 				if (ants_left_in_path(path[i]))
// 					tmp = i;
// 				else
// 					size = i;
// 			}
// 			else
// 				ant = push_ants_from_start(path, i, ant, sp);
// 			if (tmp >= 0)
// 			{
// 				push_ants_to_end(path, tmp, sp);
// 				tmp = -1;
// 			}
// 			sp = 1;
// 			i++;
// 			if (i >= size || ant >= farm->ants)
// 			{
// 				if (i >= size)
// 				{
// 					ft_printf("\n");
// 					sp = 0;
// 				}
// 				break ;
// 			}
// 		}
// 	}
// 	while (farm->endroom->antnbr + 1 != farm->ants)
// 	{
// 		if (i >= size)
// 			i = 0;
// 		while (i < size)
// 		{
// 			sp = push_ants_to_end(path, i, sp);
// 			i++;
// 			if (farm->endroom->antnbr + 1 == farm->ants)
// 				break ;
// 		}
// 		ft_printf("\n");
// 		sp = 0;
// 	}
// }

// void	run(t_farm *farm, t_path *path)
// {
// 	int		i;
// 	int		j;
// 	int		ant;

// 	i = 0;
// 	ant = 0;
// 	while (i < path->size)
// 	{
// 		if (ants_left_in_path(path[i]))
// 			push_ant_further(ant, path[i].list);
// 		if (issend(path, ant, i))
// 		{
// 			push_ants_from_start(path, i);
// 			farm->startroom->antnbr--;
// 		}
// 		ant++;
// 		i++;
// 		if (farm->startroom->antnbr == 0)
// 			break ;
// 	}
// 	j = 0;
// 	while (j < i)
// 	{
// 		push_ants_to_end(path, j);
// 		j++;
// 		if (farm->endroom->antnbr != farm->ants)
// 			return ;
// 	}
// }

void	delete_path(t_path *path, int noend)
{
	int		i;
	t_path	tmp;

	i = noend + 1;
	while (i < path->size)
	{
		ft_swap(&path[noend].index, &path[i].index);
		tmp = path[noend];
		path[noend] = path[i];
		path[i] = path[noend];
		noend++;
		i = noend + 1;
	}
	path->size--;
}

void	check_paths(t_path *path)
{
	int		i;
	t_queue	*list;

	i = 0;
	while (i < path->size)
	{
		list = path[i].list;
		while (list)
		{
			list->room->antnbr = -1;
			if (!list->next && list->room->status != 'e')
			{
				delete_path(path, i);
				i = 0;
				break ;
			}
			list = list->next;
		}
		i++;
	}
}

void	run_ants(t_farm *farm, t_path *path)
{
	farm->startroom->antnbr = farm->ants;
	check_paths(path);
	print_list(path);
	// run(farm, path);
	// free_paths(&path);
}
