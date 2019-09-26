/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_enough_paths.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:43:53 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/26 14:52:06 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_enough_paths(t_path *path, int i)
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
