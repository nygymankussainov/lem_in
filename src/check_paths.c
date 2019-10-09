/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:33:05 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/09 13:33:17 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
