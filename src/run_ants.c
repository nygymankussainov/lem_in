/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 17:57:58 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/09 18:14:29 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

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

void	push_ants_to_end(t_path *path, int size)
{
	while (size < path->size)
	{
		if (ants_left_in_path(path[size]))
			push_ant_further(path[size].endlist);
		size++;
	}
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
			{
				push_ant(path[i].list, ant);
				farm->startroom->antnbr--;
			}
			i++;
			ant++;
		}
		push_ants_to_end(path, size);
		ft_printf("\n");
	}
}

void	run_ants(t_farm *farm, t_path *path)
{
	print_valid_data(farm);
	check_paths(path);
	farm->startroom->antnbr = farm->ants;
	run(farm, path);
}
