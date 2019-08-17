/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_rooms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 10:41:55 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/17 12:10:17 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int		ifcoords(t_farm *farm, char **room)
{
	char	**allcoords;
	char	*xy;
	int		i;

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
	return (0);
}

int		check_coords(t_farm *farm, char **room)
{
	if (!farm->coords)
	{
		farm->coords = ft_strdup(room[1]);
		farm->coords = ft_strjoin(farm->coords, "*", 1, 0);
		farm->coords = ft_strjoin(farm->coords, room[2], 1, 0);
	}
	else
	{
		if (ifcoords(farm, room))
			return (1);
	}
	farm->coords = farm->coords ? ft_strjoin(farm->coords, "\n", 1, 0) :
		farm->coords;
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
	farm->room_name = !farm->room_name ? ft_strdup(room[0]) :
		ft_strjoin(farm->room_name, room[0], 1, 0);
	farm->room_name = ft_strjoin(farm->room_name, "\n", 1, 0);
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
	return (room);
}
