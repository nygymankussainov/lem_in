/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_links.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nygymankussainov <nygymankussainov@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 10:43:03 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/22 14:59:37 by nygymankuss      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

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

int		isname_exist(char **room, t_farm *farm)
{
	char	**name;
	int		i;
	int		key;
	int		j;

	name = ft_strsplit(farm->room_name, '\n');
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
	ft_free_two_dim_arr(name);
	if (key != 2)
		return (0);
	return (1);
}

char	**validate_links(char *str, t_farm *farm)
{
	char	**room;
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
	if (key != 1)
		return (0);
	i = 0;
	room = ft_strsplit(str, '-');
	while (room[i])
		i++;
	if (i != 2 || (room[0] && room[1] && !ft_strcmp(room[0], room[1]))
		|| !isname_exist(room, farm))
	{
		ft_free_two_dim_arr(room);
		return (NULL);
	}
	farm->link = farm->link ? ft_strjoin(farm->link, "\n", 1, 0) : farm->link;
	farm->link = farm->link ? ft_strjoin(farm->link, str, 1, 0) : farm->link;
	farm->link = !farm->link ? ft_strdup(str) : farm->link;
	return (room);
}
