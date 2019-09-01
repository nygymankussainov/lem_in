/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vizualizer1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 23:17:24 by hfrankly          #+#    #+#             */
/*   Updated: 2019/08/30 18:43:29 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

t_room		*ft_find_ant_room(t_farm *farm, char *str)
{
	t_hashcodes	*hc;
	t_room		*room;
	int			nbr;

	hc = farm->hashcodes;
	nbr = ft_atoi(str);
	while (hc)
	{
		room = farm->h_tab[hc->hash_code].room;
		while (room)
		{
			if (room->antnbr == nbr)
				return (room);
			room = room->next;
		}
		hc = hc->next;
	}
	room = farm->h_tab[farm->start].room;
	while (room)
	{
		if (room->status == 's')
			return (room);
		room = room->next;
	}
	return (NULL);
}

int		ft_get_link_length(const t_room *src, const t_room *dst)
{
	return (sqrt(pow((dst->x - src->x), 2) + pow(dst->y - src->y, 2)));
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
		count++;
	return (count);
}
