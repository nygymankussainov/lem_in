/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qsort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:42:16 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/14 21:33:59 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	sort_arr_path(t_path *path, int size)
{
	int		i;
	int		j;
	t_path	tmp;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (path[j].index == i)
				break ;
			j++;
		}
		tmp = path[i];
		path[i] = path[j];
		path[j] = tmp;
		i++;
	}
}

void	ft_qsort(int *s_arr, int size)
{
	int		i;
	int		j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (s_arr[i] < s_arr[j])
				ft_swap(&s_arr[i], &s_arr[j]);
			j++;
		}
		i++;
	}
}

int		*ft_path_into_array(t_path *path, int size)
{
	int		i;
	int		*array;

	i = 0;
	if (!(array = (int*)malloc(4 * size)))
		exit(0);
	while (i < size)
	{
		array[i] = path[i].steps;
		i++;
	}
	return (array);
}

void	ft_array_to_path(int *array, t_path *path, int size)
{
	int		i;
	int		j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while ((j < size && array[i] != path[j].steps) || path[j].checked)
			j++;
		path[j].index = i;
		path[j].checked = true;
		i++;
	}
}

int		sort_paths(t_path *path, int size)
{
	int		*array;
	int		i;

	i = 0;
	while (i < size - 1)
		if (path[i].steps > path[++i].steps)
			return (1);
	array = ft_path_into_array(path, size);
	ft_qsort(array, size);
	ft_array_to_path(array, path, size);
	free(array);
	array = NULL;
	return (0);
}
