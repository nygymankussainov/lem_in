/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_ants_to_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:29:46 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/17 21:46:56 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		push_ants_to_end(t_path *path, int i, int sp)
{
	t_queue	*q_path;

	q_path = path[i].queue;
	while (q_path && q_path->room->antnbr == -1)
		q_path = q_path->next;
	return (push_ant_further(-1, q_path, sp));
}
