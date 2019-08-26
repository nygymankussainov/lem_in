/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_rooms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 17:24:00 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/26 13:19:52 by vhazelnu         ###   ########.fr       */
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

int		isduplicate(t_coords *coords)
{
	t_coords	*tmp;

	while (coords->next)
	{
		tmp = coords->next;
		while (tmp)
		{
			if (coords->x == tmp->x && coords->y == tmp->y)
				return (1);
			tmp = tmp->next;
		}
		coords = coords->next;
	}
	return (0);
}

int		ifstartend(t_farm *farm, t_hashcodes **hashcodes,
	t_room **room, t_coords **coords)
{
	int		tmp;

	tmp = 0;
	farm->isst = !ft_strcmp("##start", farm->line) ? 1 : farm->isst;
	farm->isend = !ft_strcmp("##end", farm->line) ? 1 : farm->isend;
	tmp = farm->room_count;
	ft_strdel(&farm->line);
	farm->isrec = 1;
	validate_rooms(hashcodes, room, farm, coords);
	farm->isrec = 0;
	if (tmp >= farm->room_count)
		return (0);
	return (1);
}

int		validate_rooms_part2(t_hashcodes **hashcodes, t_room **room,
	t_farm *farm, t_coords **coords)
{
	if (!(farm->i = validate_coords(farm->line)))
		return (0);
	else
	{
		if (!(write_data_in_sroom(farm, room, hashcodes, coords)))
			return (0);
		farm->room_count++;
	}
	return (1);
}

int		validate_rooms(t_hashcodes **hashcodes, t_room **room,
	t_farm *farm, t_coords **coords)
{
	while (get_next_line(farm->fd, &farm->line) == 1)
	{
		if ((!ft_strcmp("##start", farm->line) ||
			!ft_strcmp("##end", farm->line)) && !farm->isrec)
		{
			if (!ifstartend(farm, hashcodes, room, coords))
				return (0);
		}
		else if (farm->line[0] == '#' && !farm->isrec)
			farm->i = farm->i;
		else if (islink(farm->line))
		{
			if (!farm->isst || !farm->isend ||
				!farm->room_count || isduplicate(*coords))
				return (0);
			return (1);
		}
		else if (!validate_rooms_part2(hashcodes, room, farm, coords))
			return (0);
		if (farm->isrec == 1)
			return (1);
		ft_strdel(&farm->line);
	}
	return (0);
}
