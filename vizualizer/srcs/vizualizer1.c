/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vizualizer1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 23:17:24 by hfrankly          #+#    #+#             */
/*   Updated: 2019/08/30 16:17:10 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

t_room		*ft_find_ant_room(t_farm *farm, char *str)
{
	t_hash_tab	*ht;
	t_hashcodes	*hc;
	t_room		*room;
	int			nbr;
	char		*newstr;

	ht = farm->h_tab;
	hc = farm->hashcodes;
	nbr = 0;
	while (str[nbr] && str[nbr] != '-')
		nbr++;
	newstr = ft_strndup(str, nbr);
	nbr = ft_atoi(newstr);
	while (hc)
	{
		room = ht[hc->hash_code].room;
		while (room)
		{
			if (room->antnbr == nbr)
				return (room);
			room = room->next;
		}
		hc = hc->next;
	}
	free(newstr);
	return (ht[farm->start].room); // не работает, если есть коллизия со стартовой комнатой
}

int		ft_get_link_length(t_sdl *sdl, const t_room *src, const t_room *dst)
{
	return (sqrt(pow(SIZEX / 2 - (SIZEY / sdl->map.maxdif)
	* (sdl->map.xcenter - (dst->x - src->x)), 2)
	+ pow(SIZEY / 2 - (SIZEY / sdl->map.maxdif)
	* (sdl->map.ycenter - (dst->y - src->y)), 2)));
}

void		free_arr(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int			ft_array_size(char **arr)
{
	int		count;

	count = 0;
	while (arr[count])
	{
		count++;
	}
	return (count);
}
