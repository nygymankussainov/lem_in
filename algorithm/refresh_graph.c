/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_graph.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:52:42 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/17 15:17:10 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*ft_return_room(t_farm *farm, char *name)
{
	int		hash;
	t_room	*room;

	hash = hash_func(name, farm->size);
	room = farm->h_tab[hash].room;
	while (room)
	{
		if (room->name == name)
			return (room);
		room = room->next;
	}
	return (NULL);
}

void	ft_refresh_room_links(t_room *room)
{
	
}

void	ft_refresh_graph(t_farm *farm)
{
	
}
