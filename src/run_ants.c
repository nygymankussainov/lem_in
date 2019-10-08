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

int		count_optimal_paths(t_path *path, int ants)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	if (path->size == 1)
		return (1);
	while (i < path->size)
	{
		if (ants >= expression(path, i))
			size++;
		else
			break ;
		i++;
		ants--;
	}
	return (size);
}

int		ants_left_in_path(t_path path)
{
	t_queue		*q_path;

	q_path = path.list->next;
	while (q_path)
	{
		if (q_path->room->antnbr > 0 && q_path->room->status != 'e')
			return (1);
		q_path = q_path->next;
	}
	return (0);
}

void	push_ant_further(t_queue *list)
{
	list = list->prev;
	while (list && list->room && !list->room->status)
	{
		if (list->room->antnbr > 0)
		{
			if (list->next->room->status == 'e')
			{
				list->next->room->antnbr++;
				ft_printf("L%d-%s ", list->room->antnbr, list->next->room->name);
			}
			else
			{
				list->next->room->antnbr = list->room->antnbr;
				ft_printf("L%d-%s ", list->next->room->antnbr, list->next->room->name);
			}
			list->room->antnbr = 0;
		}
		list = list->prev;
	}
}

void	push_ant(t_queue *list, int ant)
{
	list->next->room->antnbr = ant;
	ft_printf("L%d-%s ", ant, list->next->room->name);
}

void	run(t_farm *farm, t_path *path)
{
	int		i;
	int		size;
	int		ant;

	ant = 1;
	while (farm->endroom->antnbr != farm->ants)
	{
		size = count_optimal_paths(path, farm->startroom->antnbr);
		i = 0;
		while (i < size)
		{
			if (ants_left_in_path(path[i]))
				push_ant_further(path[i].endlist);
			if (farm->startroom->antnbr > 0)
				push_ant(path[i].list, ant);
			i++;
			ant++;
			farm->startroom->antnbr--;
		}
		while (size < path->size)
		{
			if (ants_left_in_path(path[size]))
				push_ant_further(path[size].endlist);
			size++;
		}
		ft_printf("\n");
	}
}

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
		path[i] = tmp;
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
			list->room->antnbr = 0;
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
	print_valid_data(farm);
	check_paths(path);
	farm->startroom->antnbr = farm->ants;
	run(farm, path);
}
