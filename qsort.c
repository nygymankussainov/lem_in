/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qsort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:42:16 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/14 19:21:47 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
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
