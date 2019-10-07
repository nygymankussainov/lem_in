/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_and_connect_rooms.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 13:30:36 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/07 18:43:19 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_link	*create_slink(t_room *room, char *linkname)
{
	t_link	*new;
	t_link	*tmp;

	if (room->link)
	{
		tmp = room->link;
		while (tmp)
		{
			if (!ft_strcmp(linkname, tmp->room->name))
				return (room->link);
			tmp = tmp->next;
		}
		if (!(new = (t_link *)ft_memalloc(sizeof(t_link))))
			return (NULL);
		new->next = room->link;
		room->link = new;
	}
	else if (!(room->link = (t_link *)ft_memalloc(sizeof(t_link))))
		return (NULL);
	room->link->weight = 1;
	return (room->link);
}

void	connect_rooms(t_room *room1, t_room *room2)
{
	room1->link = create_slink(room1, room2->name);
	room2->link = create_slink(room2, room1->name);
	room1->link->room = room2;
	room2->link->room = room1;
}

int		connect_collided_rooms(char *name1, char *name2,
	t_hash_tab *h_tab, int size)
{
	t_room	*room1;
	t_room	*room2;
	int		hash1;
	int		hash2;

	hash1 = hash_func(name1, size);
	hash2 = hash_func(name2, size);
	if (hash1 == hash2)
	{
		room1 = h_tab[hash1].room;
		room2 = h_tab[hash2].room;
		while (room1 && ft_strcmp(room1->name, name1) != 0)
			room1 = room1->next;
		while (room2 && ft_strcmp(room2->name, name2) != 0)
			room2 = room2->next;
		ft_strdel(&name1);
		ft_strdel(&name2);
		if (!room1 || !room2)
			return (-1);
		connect_rooms(room1, room2);
		return (1);
	}
	return (2);
}

t_room	*find_room(char *name, t_hash_tab *h_tab, int size)
{
	t_room	*tmp;
	int		hash;

	hash = hash_func(name, size);
	tmp = h_tab[hash].room;
	if (tmp)
	{
		while (tmp)
		{
			if (!ft_strcmp(name, tmp->name))
			{
				ft_strdel(&name);
				return (tmp);
			}
			tmp = tmp->next;
		}
	}
	return (NULL);
}

int		find_and_connect_rooms(char *line, t_hash_tab *h_tab, int size)
{
	t_room	*room1;
	t_room	*room2;
	char	*name1;
	char	*name2;
	int		i;

	i = 0;
	while (line[i] != '-')
		i++;
	name1 = ft_strndup(line, i);
	name2 = ft_strdup(line + i + 1);
	if ((i = connect_collided_rooms(name1, name2, h_tab, size)) == -1)
		return (0);
	if (i == 1)
		return (1);
	else if (!(room1 = find_room(name2, h_tab, size)) ||
		!(room2 = find_room(name1, h_tab, size)))
	{
		ft_strdel(&name1);
		ft_strdel(&name2);
		return (0);
	}
	connect_rooms(room1, room2);
	return (1);
}
