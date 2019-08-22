/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nygymankussainov <nygymankussainov@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:40:48 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/22 15:01:30 by nygymankuss      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// unsigned int	hash_func(char *str)
// {
//     unsigned int		hash;
//     int					c;

// 	hash = 5381;
//     while (*str)
// 	{
// 		c = *str;
//         hash = ((hash << 5) + hash) + c;
// 		str++;
// 	}
//     return (hash);
// }

int		hash_func(char *str)
{
	int		i;
	int		g;
	int		hash;

	g = 31;
	hash = 0;
	i = 0;
	while (str[i])
	{
		hash = g * hash + str[i];
		i++;
	}	
	return (hash);
}

void	get_links(t_farm *farm, t_room **room)
{
	char	**links;
	char	**tmp;
	int		i;
	int		hash1;
	int		hash2;

	links = ft_strsplit(farm->link, '\n');
	i = 0;
	while (links[i])
	{
		tmp = ft_strsplit(links[i], '-');
		hash1 = hash_func(tmp[0]);
		hash2 = hash_func(tmp[1]);
		while (room[hash1]->next && ft_strcmp(room[hash1]->name, tmp[0]) != 0)
			room[hash1] = room[hash1]->next;
		while (room[hash2]->next && ft_strcmp(room[hash2]->name, tmp[1]) != 0)
			room[hash2] = room[hash2]->next;
		room[hash1]->link = room[hash1]->link ? ft_strjoin(room[hash1]->link, "-", 1, 0) : room[hash1]->link;
		room[hash1]->link = room[hash1]->link ? ft_strjoin(room[hash1]->link, room[hash2]->name, 1, 0) : room[hash1]->link;
		room[hash1]->link = !room[hash1]->link ? ft_strdup(room[hash2]->name) : room[hash1]->link;
		room[hash2]->link = room[hash2]->link ? ft_strjoin(room[hash2]->link, "-", 1, 0) : room[hash2]->link;
		room[hash2]->link = room[hash2]->link ? ft_strjoin(room[hash2]->link, room[hash1]->name, 1, 0) : room[hash2]->link;
		room[hash2]->link = !room[hash2]->link ? ft_strdup(room[hash1]->name) : room[hash2]->link;
		ft_free_two_dim_arr(tmp);
		i++;
	}
	ft_free_two_dim_arr(links);
}

void	hash_table(t_farm *farm, t_room **room)
{
	int				hash;
	int				i;
	int				j;
	char			**allnames;
	char			**coords;

	if (!(room = (t_room **)malloc(sizeof(t_room *) * (2147483647))))
		exit(0);
	allnames = ft_strsplit(farm->room_name, '\n');
	coords = ft_strsplit(farm->coords, '\n');
	j = 0;
	while (j < farm->room_count)
	{
		hash = hash_func(allnames[j]);
		if (room[hash])
			room[hash] = room[hash]->next;
		if (!(room[hash] = (t_room *)ft_memalloc(sizeof(t_room))))
			exit(0);
		room[hash]->name = ft_strdup(allnames[j]);
		room[hash]->x = ft_atoi(coords[j]);
		i = 0;
		while (coords[j][i] != '*')
			i++;
		room[hash]->y = ft_atoi(coords[j] + i + 1);
		j++;
	}
	get_links(farm, room);
	j = 0;
	while (j < farm->room_count)
	{
		hash = hash_func(allnames[j]);
		ft_printf("%s", room[hash]->name);
		if (room[hash]->link)
			ft_printf("-%s ", room[hash]->link);
		else
			ft_printf(" ");
		ft_printf("%d %d\n", room[hash]->x, room[hash]->y);
		j++;
	}
	ft_free_two_dim_arr(allnames);
	ft_free_two_dim_arr(coords);
}
