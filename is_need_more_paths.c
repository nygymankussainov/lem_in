/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_need_more_paths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:43:53 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/01 20:16:59 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_need_more_paths(int ants, t_path **path)
{
	int		i;
	int		j;
	int		res;

	i = (*path)->size;
	res = 0;
	j = 0;
	if ((*path)->size < 3)
	{
		res = (*path + 1)->steps - (*path + 0)->steps;
		if (ants - 1 > res)
			return (1);
		return (0);
	}
	ants -= 2;
	while (i-- > 0 && j < (*path)->size)
	{
		res = res + (*path + i)->steps - (*path + j)->steps;
		ants--;
		j++;
	}
	if (ants > res)
		return (1);
	return (0);
}
