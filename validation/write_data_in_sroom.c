/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_data_in_sroom.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 18:03:57 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/14 12:14:59 by vhazelnu         ###   ########.fr       */
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

int		is_collision_and_duplicate(t_hash_tab *h_tab, t_coords *coords,
	t_farm *farm, t_hashcodes **hashcodes)
{
	int			hash;
	t_room		*tmp;

	hash = hash_func(farm->name, farm->size);
	tmp = h_tab[hash].room;
	if (tmp)
		while (tmp)
		{
			if (!ft_strcmp(tmp->name, farm->name))
				return (0);
			tmp = tmp->next;
		}
	if (!(tmp = (t_room *)ft_memalloc(sizeof(t_room))))
		return (0);
	tmp->path = -1;
	tmp->name = ft_strdup(farm->name);
	tmp->x = coords->x;
	tmp->y = coords->y;
	tmp->next = h_tab[hash].room;
	tmp->link = NULL;
	h_tab[hash].room = tmp;
	write_hashcode_in_struct(hash, hashcodes);
	return (1);
}

int		write_data_in_sroom(t_farm *farm, t_hash_tab *h_tab,
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
	if (!is_collision_and_duplicate(h_tab, *coords, farm, hashcodes))
	{
		free_coords(coords);
		ft_strdel(&farm->name);
		return (0);
	}
	ft_strdel(&farm->name);
	return (1);
}
