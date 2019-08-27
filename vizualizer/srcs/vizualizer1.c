/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vizualizer1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 23:17:24 by hfrankly          #+#    #+#             */
/*   Updated: 2019/08/25 23:19:14 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_find_ant_room(t_farm *farm, int antnbr)
{
	int i;

	i = -1;
	while (++i < farm->room_count)
		if (farm->room[i].antnbr == antnbr)
			return (i);
	return (farm->start);
}

int		ft_get_link_length(t_sdl *sdl, t_room src, t_room dst)
{
	return (sqrt(pow(SIZEX / 2 - (SIZEY / sdl->map.maxdif)
	* (sdl->map.xcenter - (dst.x - src.x)), 2)
	+ pow(SIZEY / 2 - (SIZEY / sdl->map.maxdif)
	* (sdl->map.ycenter - (dst.y - src.y)), 2)));
}
