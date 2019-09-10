/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_rooms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 17:24:00 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/10 20:46:39 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int		islink(char *line)
{
	while (*line)
	{
		if (*line == '-' && *(line - 1) != ' ')
			return (1);
		line++;
	}
	return (0);
}

void	mark_room(t_farm *farm, t_hash_tab *h_tab, char *name, char c)
{
	t_room	*room;

	farm->start = c == 's' ? hash_func(name, farm->size) : farm->start;
	farm->end = c == 'e' ? hash_func(name, farm->size) : farm->end;
	room = c == 's' ? h_tab[farm->start].room : h_tab[farm->end].room;
	room->dist = c == 's' ? 0 : room->dist;
	while (room)
	{
		if (!ft_strcmp(room->name, name))
		{
			room->status = c;
			return ;
		}
		room = room->next;
	}
}

int		ifstartend(t_farm *farm, t_hashcodes **hashcodes,
	t_hash_tab *h_tab, t_coords **coords)
{
	int		tmp;
	char	*name;
	char	c;

	if ((!ft_strcmp("##start", farm->line) && farm->start != -1) ||
		(!ft_strcmp("##end", farm->line) && farm->end != -1))
		return (0);
	tmp = farm->room_count;
	c = !ft_strcmp("##start", farm->line) ? 's' : 'e';
	ft_strdel(&farm->line);
	farm->recur = 1;
	validate_rooms(hashcodes, h_tab, farm, coords);
	if (tmp >= farm->room_count)
		return (0);
	tmp = 0;
	while (farm->line[tmp] != ' ')
		tmp++;
	name = ft_strndup(farm->line, tmp);
	farm->recur = 0;
	mark_room(farm, h_tab, name, c);
	ft_strdel(&name);
	return (1);
}

int		validate_rooms_part2(t_hashcodes **hashcodes, t_hash_tab *h_tab,
	t_farm *farm, t_coords **coords)
{
	if (!(farm->i = validate_coords(farm->line)))
		return (0);
	else
	{
		if (!(write_data_in_sroom(farm, h_tab, hashcodes, coords)))
			return (0);
		farm->room_count++;
	}
	return (1);
}

int		validate_rooms(t_hashcodes **hashcodes, t_hash_tab *h_tab,
	t_farm *farm, t_coords **coords)
{
	while (get_next_line(farm->fd, &farm->line) == 1)
	{
		if ((!ft_strcmp("##start", farm->line) ||
			!ft_strcmp("##end", farm->line)) && !farm->recur)
		{
			if (!ifstartend(farm, hashcodes, h_tab, coords))
				return (0);
		}
		else if (farm->line[0] == '#' && !farm->recur)
			farm->i = farm->i;
		else if (islink(farm->line))
		{
			if (farm->start < 0 || farm->end < 0 ||
				!farm->room_count || isduplicate(*coords))
				return (0);
			return (1);
		}
		else if (!validate_rooms_part2(hashcodes, h_tab, farm, coords))
			return (0);
		if (farm->recur == 1)
			return (1);
		ft_strdel(&farm->line);
	}
	return (0);
}
