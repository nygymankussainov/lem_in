/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 16:04:51 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/16 20:12:21 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		isdash(char *str)
{
	while (*str)
	{
		if (*str == '-')
			return (1);
		str++;
	}
	return (0);
}

char	**validate_rooms(char *str, t_farm *farm)
{
	char	**room;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			j++;
		i++;
	}
	if (j > 2)
		return (0);
	room = ft_strsplit(str, ' ', '\t');
	i = 0;
	while (room[i])
		i++;
	if (i != 3 || isdash(room[0]) ||
		!isint(room[1], farm, 'r') || !isint(room[2], farm, 'r'))
	{
		ft_free_two_dim_arr(room);
		return (NULL);
	}
	// farm->x = ft_atoi(room[1]);
	// farm->y = ft_atoi(room[2]);
	return (room);
}

char	**validate_links(char *str, t_farm *farm)
{
	char	**room;
	char	**name;
	int		j;
	int		i;
	int		key;

	i = 0;
	key = 0;
	while (str[i])
	{
		if (str[i] == '-')
			key++;
		i++;
	}
	if (key > 1)
		return (0);
	i = 0;
	room = ft_strsplit(str, '-', '-');
	while (room[i])
		i++;
	if (i != 2 || (room[0] && room[1] && !ft_strcmp(room[0], room[1])))
	{
		ft_free_two_dim_arr(room);
		return (NULL);
	}
	name = ft_strsplit(farm->room_name, '\n', '\n');
	i = 0;
	key = 0;
	while (room[i])
	{
		j = 0;
		while (name[j])
			if (!ft_strcmp(room[i], name[j++]))
				key++;
		i++;
	}
	if (key != 2)
	{
		ft_free_two_dim_arr(room);
		ft_free_two_dim_arr(name);
		return (NULL);
	}
	ft_free_two_dim_arr(name);
	return (room);
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
	free(*line);
	*line = NULL;
	if (!validation(fd, farm, 1, line) || tmp == farm->room_count)
		return (0);
	if (status == 's')
		farm->start = ft_strdup(*line);
	else if (status == 'e')
		farm->end = ft_strdup(*line);
	return (1);
}

int		check_coords(t_farm *farm, char **room)
{
	char	**allcoords;
	char	*xy;
	int		i;

	if (!farm->coords)
	{
		farm->coords = ft_strdup(room[1]);
		farm->coords = ft_strjoin(farm->coords, "*", 1, 0);
		farm->coords = ft_strjoin(farm->coords, room[2], 1, 0);
	}
	else
	{
		xy = ft_strdup(room[1]);
		xy = ft_strjoin(xy, "*", 1, 0);
		xy = ft_strjoin(xy, room[2], 1, 0);
		allcoords = ft_strsplit(farm->coords, '\n', '\n');
		i = 0;
		while (allcoords[i])
		{
			if (!ft_strcmp(allcoords[i], xy))
			{
				free(xy);
				xy = NULL;
				ft_free_two_dim_arr(allcoords);
				ft_free_two_dim_arr(room);
				return (1);
			}
			i++;
		}
		farm->coords = ft_strjoin(farm->coords, xy, 1, 1);
		ft_free_two_dim_arr(allcoords);
	}
	farm->coords = farm->coords ? ft_strjoin(farm->coords, "\n", 1, 0) : farm->coords;
	return (0);
}

int		duplicate(t_farm *farm, char **room)
{
	char	**allnames;
	int		i;

	if (farm->room_name)
	{
		allnames = ft_strsplit(farm->room_name, '\n', '\n');
		i = 0;
		while (allnames[i])
		{
			if (!ft_strcmp(allnames[i], room[0]))
			{
				ft_free_two_dim_arr(allnames);
				ft_free_two_dim_arr(room);
				return (1);
			}
			i++;
		}
		ft_free_two_dim_arr(allnames);
	}
	if (check_coords(farm, room))
		return (1);
	farm->room_name = !farm->room_name ? ft_strdup(room[0]) : ft_strjoin(farm->room_name, room[0], 1, 0);
	farm->room_name = ft_strjoin(farm->room_name, "\n", 1, 0);
	return (0);
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
		else if ((!ft_strcmp("##start", *line) || !ft_strcmp("##end", *line)) && !isrec)
		{
			if (!ifstartend(farm, line, fd))
			{
				free(*line);
				*line = NULL;
				return (0);
			}
		}
		else if ((*line)[0] == '#' && (*line)[1] == '#')
		{
			free(*line);
			*line = NULL;
		}
		else if ((*line)[0] == '#' && (*line)[1] != '#')
		{
			farm->output = ft_strjoin(farm->output, *line, 1, 0);
			farm->output = ft_strjoin(farm->output, "\n", 1, 0);
		}
		else if (!farm->link_count && (room = validate_rooms(*line, farm)) != NULL && !duplicate(farm, room))
			ifroomlinks(farm, room, 'r');
		else if (farm->room_count && (room = validate_links(*line, farm)) != NULL)
			ifroomlinks(farm, room, 'l');
		else if (!**line)
		{
			free(*line);
			*line = NULL;
			if (!farm->start || !farm->end || !farm->ants || !farm->link_count
				|| !farm->room_count)
				return (0);
			return (1);
		}
		else
		{
			free(*line);
			*line = NULL;
			get_next_line(fd, line);
			free(*line);
			*line = NULL;
			return (0);
		}
		if (isrec)
			return (1);
		free(*line);
		*line = NULL;
	}
	if (!farm->start || !farm->end || !farm->ants || !farm->link_count
		|| !farm->room_count)
		return (0);
	return (1);
}
