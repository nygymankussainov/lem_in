/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 15:27:17 by hfrankly          #+#    #+#             */
/*   Updated: 2019/08/25 14:12:14 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_map	ft_initmap(t_farm farm, int *maxcoords)
{
	t_map map;

	if (maxcoords[0] - maxcoords[2] < maxcoords[1] - maxcoords[3])
		map.maxdif = abs(maxcoords[1] - maxcoords[3]) + 2;
	else
		map.maxdif = abs(maxcoords[0] - maxcoords[2]) + 2;
	map.xcenter = ft_find_max_infarm(farm, 'x')
	- (maxcoords[0] - maxcoords[2]) / 2;
	map.ycenter = ft_find_max_infarm(farm, 'y')
	- (maxcoords[1] - maxcoords[3]) / 2;
	free(maxcoords);
	return (map);
}

int		ft_find_max_infarm(t_farm farm, char c)
{
	int		max;
	int		i;

	max = -2147483648;
	i = -1;
	if (c == 'x')
		while (++i < farm.room_count)
			if (max < farm.room[i].x)
				max = farm.room[i].x;
	if (c == 'y')
		while (++i < farm.room_count)
			if (max < farm.room[i].y)
				max = farm.room[i].y;
	return (max);
}

int		ft_find_min_infarm(t_farm farm, char c)
{
	int		min;
	int		i;

	min = 2147483647;
	i = -1;
	if (c == 'x')
		while (++i < farm.room_count)
			if (min > farm.room[i].x)
				min = farm.room[i].x;
	if (c == 'y')
		while (++i < farm.room_count)
			if (min > farm.room[i].y)
				min = farm.room[i].y;
	return (min);
}

int		*ft_find_maxcoords(t_farm farm)
{
	int		i;
	int		*maxcoords;

	i = -1;
	if (!(maxcoords = (int*)malloc(4 * 4)))
		exit(0);
	maxcoords[0] = ft_find_max_infarm(farm, 'x');
	maxcoords[1] = ft_find_max_infarm(farm, 'y');
	maxcoords[2] = ft_find_min_infarm(farm, 'x');
	maxcoords[3] = ft_find_min_infarm(farm, 'y');
	return (maxcoords);
}
