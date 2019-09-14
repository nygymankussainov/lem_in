/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qsort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:42:16 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/14 21:37:48 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_if_sort(t_path *path, int size)
{
	int		i;

	i = 0;
	while (i < size - 1)
	{
		if (path[i].steps > path[i + 1].steps)
			return (0);
		i++;
	}
	return (1);
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

	if (ft_if_sort(path, size))
		return (1);
	array = ft_path_into_array(path, size);
	ft_qsort(array, size);
	ft_array_to_path(array, path, size);
	free(array);
	array = NULL;
	return (0);
}
