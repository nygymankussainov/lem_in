/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:56:41 by hfrankly          #+#    #+#             */
/*   Updated: 2019/10/09 22:50:47 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

void	ft_change_coords(t_sdl *sdl)
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
