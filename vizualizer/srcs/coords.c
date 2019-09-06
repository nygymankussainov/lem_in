/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 15:27:17 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/06 13:43:17 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

void		ft_change_coords(t_sdl *sdl)
{
	t_hash_tab	*ht;
	t_hashcodes	*hc;
	t_room		*room;

	sdl->map = ft_initmap(sdl->farm, ft_find_maxcoords(sdl->farm));
	ht = sdl->farm->h_tab;
	hc = sdl->farm->hashcodes;
	while (hc)
	{
		room = ht[hc->hash_code].room;
		while (room)
		{
			room->x = SIZEX / 2 - (SIZEX / sdl->map.maxdif)
			* (sdl->map.xcenter - room->x);
			room->y = SIZEY / 2 - (SIZEY / sdl->map.maxdif)
			* (sdl->map.ycenter - room->y);
			room->antnbr = -1;
			room = room->next;
		}
		hc = hc->next;
	}
}

t_map	ft_initmap(t_farm *farm, int *maxcoords)
{
	t_map	map;
	int		i;

	i = -1;
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
	t_room		*room;
	int			max;

	max = -2147483648;
	hc = farm->hashcodes;
	if (c == 'x')
		while (hc)
		{
			room = farm->h_tab[hc->hash_code].room;
			while (room)
			{
				if (max < room->x)
					max = room->x;
				room = room->next;
			}
			hc = hc->next;
		}	
	else
		while (hc)
		{
			room = farm->h_tab[hc->hash_code].room;
			while (room)
			{
				if (max < room->y)
					max = room->y;
				room = room->next;
			}
			hc = hc->next;
		}	
	return (max);
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
			while (room)
			{
				if (min > room->x)
					min = room->x;
				room = room->next;
			}
			hc = hc->next;
		}	
	else
		while (hc)
		{
			room = farm->h_tab[hc->hash_code].room;
			while (room)
			{
				if (min > room->y)
					min = room->y;
				room = room->next;
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
