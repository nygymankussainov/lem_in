/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vizualizer1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 23:17:24 by hfrankly          #+#    #+#             */
/*   Updated: 2019/08/28 14:14:33 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

t_room		*ft_find_ant_room(t_farm *farm, char *str)
{
	t_hash_tab	*ht;
	t_hashcodes	*hc;
	t_room		*room;

	ht = farm->h_tab;
	hc = farm->hashcodes;
	while (hc)
	{
		room = ht[hc->hash_code].room;
		while (room)
		{
			if (ht[hc->hash_code].room->antnbr == hash_func(str)
			&& !ft_strcmp(ht[hc->hash_code].room->name, str))
				return (room);
			room = room->next;
		}
		hc = hc->next;
	}
	return (ht[farm->start].room); // не работает, если есть коллизия со стартовой комнатой
}

int		ft_get_link_length(t_sdl *sdl, const t_room *src, const t_room *dst)
{
	return (sqrt(pow(SIZEX / 2 - (SIZEY / sdl->map.maxdif)
	* (sdl->map.xcenter - (dst->x - src->x)), 2)
	+ pow(SIZEY / 2 - (SIZEY / sdl->map.maxdif)
	* (sdl->map.ycenter - (dst->y - src->y)), 2)));
}
