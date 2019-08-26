/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_data_in_sroom.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 18:03:57 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/26 13:21:49 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	free_coords(t_coords **coords)
{
	t_coords	*tmp;

	if (!*coords)
		return ;
	while (*coords)
	{
		tmp = (*coords)->next;
		free(*coords);
		*coords = NULL;
		*coords = tmp;
	}
}

int		write_coords_in_struct(char *line, t_coords **coords, int i)
{
	t_coords	*new;

	if (!*coords)
	{
		if (!(*coords = (t_coords *)ft_memalloc(sizeof(t_coords))))
			return (0);
		(*coords)->x = ft_atoi(line + ++i);
		while (line[i] != ' ')
			i++;
		(*coords)->y = ft_atoi(line + i + 1);
	}
	else
	{
		if (!(new = (t_coords *)ft_memalloc(sizeof(t_coords))))
			return (0);
		new->next = *coords;
		new->x = ft_atoi(line + ++i);
		while (line[i] != ' ')
			i++;
		new->y = ft_atoi(line + i + 1);
		*coords = new;
	}
	return (1);
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

int		is_collision_and_duplicate(t_room **room, t_coords *coords,
	char *name, t_hashcodes **hashcodes)
{
	int	hash;

	hash = hash_func(name);
	if (is_room_exist(hash, *hashcodes))
	{
		while (room[hash])
		{
			if (!ft_strcmp(room[hash]->name, name))
				return (0);
			room[hash] = room[hash]->next;
		}
	}
	if (!(room[hash] = (t_room *)ft_memalloc(sizeof(t_room))))
		return (0);
	room[hash]->name = ft_strdup(name);
	room[hash]->x = coords->x;
	room[hash]->y = coords->y;
	room[hash]->next = NULL;
	room[hash]->link = NULL;
	write_hashcode_in_struct(hash, hashcodes);
	return (1);
}

int		write_data_in_sroom(t_farm *farm, t_room **room,
	t_hashcodes **hashcodes, t_coords **coords)
{
	while (farm->line[farm->i] != ' ')
		farm->i++;
	if (!write_coords_in_struct(farm->line, coords, farm->i))
	{
		free_coords(coords);
		return (0);
	}
	farm->name = ft_strndup(farm->line, farm->i);
	if (!is_collision_and_duplicate(room, *coords, farm->name, hashcodes))
	{
		free_coords(coords);
		ft_strdel(&farm->name);
		return (0);
	}
	ft_strdel(&farm->name);
	return (1);
}
