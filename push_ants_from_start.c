/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_ants_from_start.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 16:51:34 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/17 21:52:51 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		print_ant_move(t_queue *q_path, int ant, int sp)
{
	int		save;

	save = -1;
	if (q_path->next->room->status != 'e')
	{
		save = q_path->room->antnbr;
		q_path->room->antnbr = ant;
		if (q_path->next->room->antnbr >= 0)
			sp = push_ant_further(save, q_path->next, sp);
		if (q_path->next->room->antnbr != save)
		{
			if (sp)
				ft_printf(" ");
			q_path->next->room->antnbr = save;
			ft_printf("L%d-%s", save + 1, q_path->next->room->name);
			sp = 1;
		}
		if (ant >= 0)
		{
			if (sp)
				ft_printf(" ");
			ft_printf("L%d-%s", ant + 1, q_path->room->name);
		}
	}
	else
	{
		if (sp)
			ft_printf(" ");
		q_path->next->room->antnbr++;
		ft_printf("L%d-%s", q_path->room->antnbr + 1, q_path->next->room->name);
		q_path->room->antnbr = -1;
	}
	return (save);
}

int		push_ant_further(int ant, t_queue *q_path, int sp)
{
	int		save;

	save = -1;
	if (q_path && q_path->next)
	{
		save = print_ant_move(q_path, ant, sp);
		if (q_path->next->room->antnbr < 0)
			sp = push_ant_further(save, q_path->next, sp);
		else
			sp = 1;
		return (sp);
	}
	else
		return (sp);
}

int		push_ants_from_start(t_path *path, int i, int ant, int sp)
{
	t_queue	*q_path;
	int		save;

	q_path = path[i].queue;
	save = -1;
	if (q_path && (q_path->room->antnbr < 0 || q_path->room->status == 'e'))
	{
		if (sp)
			ft_printf(" ");
		if (q_path->room->status == 'e')
		{
			q_path->room->antnbr++;
			ft_printf("L%d-%s", ant + 1, q_path->room->name);
		}
		else
		{
			q_path->room->antnbr = ant;
			ft_printf("L%d-%s", q_path->room->antnbr + 1, q_path->room->name);
		}
		return (ant + 1);
	}
	if (q_path && q_path->next &&
		(q_path->next->room->antnbr < 0 || q_path->next->room->status == 'e'))
	{
		save = print_ant_move(q_path, ant, sp);
		sp = 1;
		if (q_path->next->room->status == 'e')
		{
			ant = push_ants_from_start(path, i, ant, sp);
			return (ant);
		}
	}
	else if (q_path)
		sp = push_ant_further(ant, q_path, sp);
	return (ant + 1);
}
