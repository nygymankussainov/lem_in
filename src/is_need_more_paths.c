/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_need_more_paths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:43:53 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/14 15:35:19 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int		is_need_more_paths(int ants, t_path **path)
{
	int		i;
	int		j;
	int		sum;

	i = (*path)->size;
	sum = 0;
	j = 0;
	while (--i > 0 && j < (*path)->size)
	{
		sum = sum + (*path + i)->steps - (*path + j)->steps;
		j++;
	}
	if (ants <= sum)
	{
		free_paths(path);
		return (0);
	}
	return (1);
}
