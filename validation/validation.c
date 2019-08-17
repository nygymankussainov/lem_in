/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 16:04:51 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/17 12:10:22 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	freeline(char **line)
{
	free(*line);
	*line = NULL;
}

void	ifroomlinks(t_farm *farm, char **room, char c)
{
	int		i;

	i = !farm->output ? 1 : 0;
	farm->output = !farm->output ? ft_strdup(room[0]) : farm->output;
	while (room[i])
	{
		if (i > 0)
			farm->output = c == 'l' ? ft_strjoin(farm->output, "-", 1, 0) :
				ft_strjoin(farm->output, " ", 1, 0);
		farm->output = ft_strjoin(farm->output, room[i], 1, 0);
		i++;
	}
	farm->output = ft_strjoin(farm->output, "\n", 1, 0);
	farm->link_count += c == 'l' ? 1 : 0;
	farm->room_count += c == 'r' ? 1 : 0;
	ft_free_two_dim_arr(room);
}

int		ifstartend(t_farm *farm, char **line, int fd)
{
	int		tmp;
	char	status;

	farm->output = ft_strjoin(farm->output, *line, 1, 0);
	farm->output = ft_strjoin(farm->output, "\n", 1, 0);
	tmp = farm->room_count;
	if (!ft_strcmp("##start", *line))
		status = 's';
	else if (!ft_strcmp("##end", *line))
		status = 'e';
	freeline(line);
	if (!validation(fd, farm, 1, line) || tmp == farm->room_count)
		return (0);
	if (status == 's')
		farm->start = ft_strdup(*line);
	else if (status == 'e')
		farm->end = ft_strdup(*line);
	return (1);
}

int		validation(int fd, t_farm *farm, int isrec, char **line)
{
	char	**room;

	while ((get_next_line(fd, line)) == 1)
	{
		if (isint(*line, farm, 'a') && !farm->ants)
		{
			farm->ants = ft_atoi(*line);
			farm->output = ft_itoa(farm->ants);
			farm->output = ft_strjoin(farm->output, "\n", 1, 0);
		}
		else if ((!ft_strcmp("##start", *line) ||
			!ft_strcmp("##end", *line)) && !isrec)
		{
			if (!ifstartend(farm, line, fd))
			{
				freeline(line);
				return (0);
			}
		}
		else if ((*line)[0] == '#' && (*line)[1] == '#')
			freeline(line);
		else if ((*line)[0] == '#' && (*line)[1] != '#')
		{
			farm->output = ft_strjoin(farm->output, *line, 1, 0);
			farm->output = ft_strjoin(farm->output, "\n", 1, 0);
		}
		else if (!farm->link_count && (room = validate_rooms(*line, farm))
			&& !duplicate(farm, room))
			ifroomlinks(farm, room, 'r');
		else if (farm->room_count && (room = validate_links(*line, farm)))
			ifroomlinks(farm, room, 'l');
		else if (!**line)
		{
			freeline(line);
			if (!farm->start || !farm->end || !farm->ants || !farm->link_count
				|| !farm->room_count)
				return (0);
			return (1);
		}
		else if (farm->room_count && farm->link_count)
			break ;
		else
		{
			freeline(line);
			get_next_line(fd, line);
			freeline(line);
			return (0);
		}
		if (isrec)
			return (1);
		freeline(line);
	}
	if (!farm->start || !farm->end || !farm->ants || !farm->link_count
		|| !farm->room_count)
		return (0);
	if (*line)
		freeline(line);
	return (1);
}
