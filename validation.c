/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 16:04:51 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/15 21:41:10 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		isdash(char *str)
{
	while (*str)
	{
		if (*str == '-')
			return (0);
		str++;
	}
	return (1);
}

char	**validate_rooms(char *str, t_farm *farm)
{
	char	**room;
	int		i;

	room = ft_strsplit(str, ' ', '\t');
	i = 0;
	while (room[i])
		i++;
	if (i != 3 || !isdash(room[0]) ||
		!isint(room[1], farm, 'r') || !isint(room[2], farm, 'r'))
	{
		ft_free_two_dim_arr(room);
		return (NULL);
	}
	return (room);
}

int		validation(int fd, t_farm *farm)
{
	char	*line;
	char	**room;
	int		i;
	int		tmp;

	i = 0;
	while ((get_next_line(fd, &line)) == 1)
	{
		if (isint(line, farm, 'a'))
		{
			farm->ants = ft_atoi(line);
			farm->output = ft_itoa(farm->ants);
		}
		else if (!ft_strcmp("##start", line) || !ft_strcmp("##end", line))
		{
			farm->output = ft_strjoin(farm->output, "\n", 1, 0);
			farm->output = ft_strjoin(farm->output, line, 1, 0);
			tmp = farm->room_count;
			if ((validation(fd, farm) != 1) || tmp == farm->room_count)
			{
				free(line);
				line = NULL;
				return (0);
			}
		}
		else if (line[0] == '#' && line[1] != '#')
		{
			farm->output = ft_strjoin(farm->output, "\n", 1, 0);
			farm->output = ft_strjoin(farm->output, line, 1, 0);
		}
		else if ((room = validate_rooms(line, farm)) != NULL)
		{
			while (room[i])
			{
				farm->output = ft_strjoin(farm->output, "\n", 1, 0);
				farm->output = ft_strjoin(farm->output, room[i], 1, 0);
				i++;
			}
			farm->room_count++;
			ft_free_two_dim_arr(room);
		}
		else
			return (0);
		free(line);
		line = NULL;
	}
	return (1);
}
