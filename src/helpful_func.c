/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpful_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:06:19 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/09 18:43:18 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_room	*find_startend(t_room *room, char c)
{
	while (room)
	{
		if (room->status == c)
		{
			room->visited = c == 's' ? 1 : room->visited;
			return (room);
		}
		room = room->next;
	}
	return (NULL);
}

int		is_room_exist(int hash, t_hashcodes *hashcodes)
{
	while (hashcodes)
	{
		if (hash == hashcodes->hash_code)
			return (1);
		hashcodes = hashcodes->next;
	}
	return (0);
}
