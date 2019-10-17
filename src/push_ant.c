/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_ant.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:34:28 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/17 14:06:28 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
				ft_printf("L%d-%s ", list->room->antnbr,
					list->next->room->name);
			}
			else
			{
				list->next->room->antnbr = list->room->antnbr;
				ft_printf("L%d-%s ", list->next->room->antnbr,
					list->next->room->name);
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
