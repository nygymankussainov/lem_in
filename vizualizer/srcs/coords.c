/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 15:27:17 by hfrankly          #+#    #+#             */
/*   Updated: 2019/08/27 22:28:41 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

t_map	ft_initmap(t_farm *farm, int *maxcoords)
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

int		ft_find_max_infarm(t_farm *farm, char c)
{
	t_hashcodes *hc;
	int		max;

	max = -2147483648;
	hc = farm->hashcodes;
	if (c == 'x')
		while (hc)
		{
			if (max < farm->h_tab[hc->hash_code].room->x)
				max = farm->h_tab[hc->hash_code].room->x;
			while (hc && farm->h_tab[hc->hash_code].room->next)
			{
				hc = hc->next;
				if (max < farm->h_tab[hc->hash_code].room->x)
					max = farm->h_tab[hc->hash_code].room->x;
			}
			hc = hc->next;
		}	
	else if (c == 'y')
		while (hc)
		{
			if (max < farm->h_tab[hc->hash_code].room->x)
				max = farm->h_tab[hc->hash_code].room->x;
			while (hc && farm->h_tab[hc->hash_code].room->next)
			{
				hc = hc->next;
				if (max < farm->h_tab[hc->hash_code].room->x)
					max = farm->h_tab[hc->hash_code].room->x;
			}
			hc = hc->next;
		}	
	return (max);
}

int		ft_find_min_infarm(t_farm *farm, char c)
{
	t_hashcodes *hc;
	int			min;

	min = 2147483647;
	if (c == 'x')
		while (hc)
		{
			if (min > farm->h_tab[hc->hash_code].room->y)
				min = farm->h_tab[hc->hash_code].room->y;
			while (hc && farm->h_tab[hc->hash_code].room->next)
			{
				hc = hc->next;
				if (min > farm->h_tab[hc->hash_code].room->y)
					min = farm->h_tab[hc->hash_code].room->y;
			}
			hc = hc->next;
		}	
	else if (c == 'y')
		while (hc)
		{
			if (min > farm->h_tab[hc->hash_code].room->y)
				min = farm->h_tab[hc->hash_code].room->y;
			while (hc && farm->h_tab[hc->hash_code].room->next)
			{
				hc = hc->next;
				if (min > farm->h_tab[hc->hash_code].room->y)
					min = farm->h_tab[hc->hash_code].room->y;
			}
			hc = hc->next;
		}
	return (min);
}

int		*ft_find_maxcoords(t_farm *farm)
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
