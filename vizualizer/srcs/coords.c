/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 15:27:17 by hfrankly          #+#    #+#             */
/*   Updated: 2019/10/09 22:51:53 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

void	ft_find_max_coord(t_room *room, int *max, char c)
{
	if (c == 'x')
		while (room)
		{
			if (*max < room->x)
				*max = room->x;
			room = room->next;
		}
	else
		while (room)
		{
			if (*max < room->y)
				*max = room->y;
			room = room->next;
		}
}

int		ft_find_max_infarm(t_farm *farm, char c)
{
	t_hashcodes *hc;
	t_room		*room;
	int			max;

	max = -2147483648;
	hc = farm->hashcodes;
	if (c == 'x')
		while (hc)
		{
			room = farm->h_tab[hc->hash_code].room;
			ft_find_max_coord(room, &max, 'x');
			hc = hc->next;
		}
	else
		while (hc)
		{
			room = farm->h_tab[hc->hash_code].room;
			ft_find_max_coord(room, &max, 'y');
			hc = hc->next;
		}
	return (max);
}

void	ft_find_min_coord(t_room *room, int *min, char c)
{
	if (c == 'x')
		while (room)
		{
			if (*min > room->x)
				*min = room->x;
			room = room->next;
		}
	else
		while (room)
		{
			if (*min > room->x)
				*min = room->x;
			room = room->next;
		}
}

int		ft_find_min_infarm(t_farm *farm, char c)
{
	t_hashcodes *hc;
	t_room		*room;
	int			min;

	min = 2147483647;
	hc = farm->hashcodes;
	if (c == 'x')
		while (hc)
		{
			room = farm->h_tab[hc->hash_code].room;
			ft_find_min_coord(room, &min, 'x');
			hc = hc->next;
		}
	else
		while (hc)
		{
			room = farm->h_tab[hc->hash_code].room;
			ft_find_min_coord(room, &min, 'y');
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
