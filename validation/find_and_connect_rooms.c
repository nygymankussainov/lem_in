/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_and_connect_rooms.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 13:30:36 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/26 19:15:04 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	connect_rooms(t_room *room1, t_room *room2)
{
	room1->link = create_slink(room1, room2->name);
	room2->link = create_slink(room2, room1->name);
	if (room1->link->name && room2->link->name)
		return ;
	room1->link->name = ft_strdup(room2->name);
	room2->link->name = ft_strdup(room1->name);
}

t_room	*find_room(int hash, char *name, t_room **room, t_hashcodes *hashcodes)
{
	if (is_room_exist(hash, hashcodes))
	{
		while (room[hash])
		{
			if (!ft_strcmp(name, room[hash]->name))
				return (room[hash]);
			room[hash] = room[hash]->next;
		}
	}
	return (NULL);
}

int		find_and_connect_rooms(char *line, t_room **room,
	t_hashcodes *hashcodes)
{
	int		hash1;
	int		hash2;
	char	*name1;
	char	*name2;
	int		i;

	i = 0;
	while (line[i] != '-')
		i++;
	name1 = ft_strndup(line, i);
	hash1 = hash_func(name1);
	name2 = ft_strdup(line + i + 1);
	hash2 = hash_func(name2);
	if (!(room[hash1] = find_room(hash1, name1, room, hashcodes)) ||
		!(room[hash2] = find_room(hash2, name2, room, hashcodes)))
	{
		ft_strdel(&name1);
		ft_strdel(&name2);
		return (0);
	}
	connect_rooms(room[hash1], room[hash2]);
	ft_strdel(&name1);
	ft_strdel(&name2);
	return (1);
}
