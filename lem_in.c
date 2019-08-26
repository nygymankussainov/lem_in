/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:04:16 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/26 12:33:53 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	mark_room(int fd, t_room **room, char **line, char c)
{
	int		i;
	char	*name;

	i = 0;
	ft_strdel(line);
	get_next_line(fd, line);
	while ((*line)[i] != ' ')
		i++;
	name = ft_strndup(*line, i);
	i = hash_func(name);
	if (room[i]->next)
	{
		while (room[i])
		{
			if (!ft_strcmp(room[i]->name, name))
				break ;
			room[i] = room[i]->next;
		}
	}
	room[i]->status = c;
	ft_strdel(&name);
	if (c == 's')
		ft_printf("##start\n");
	else
		ft_printf("##end\n");
}

int		isroom(char *line)
{
	int i;
	int	sp;

	i = 0;
	sp = 0;
	while (line[i])
	{
		if (line[i] == ' ')
		{
			if (!ft_isdigit(line[i + 1]))
			{
				if (line[i + 1] == '-' || line[i + 1] == '+')
				{
					if (!ft_isdigit(line[i + 2]))
						return (0);
				}
				else
					return (0);
			}
			sp++;
		}
		i++;
	}
	return (sp != 2 ? 0 : 1);
}

void	free_all_structs(t_hashcodes *hashcodes, t_room **room, t_farm *farm)
{
	t_link		*tmp;
	t_hashcodes	*tmp1;
	t_room		*tmp2;

	while (hashcodes)
	{
		tmp1 = hashcodes->next;
		while (room[hashcodes->hash_code])
		{
			tmp2 = room[hashcodes->hash_code]->next;
			while (room[hashcodes->hash_code]->link)
			{
				tmp = room[hashcodes->hash_code]->link->next;
				ft_strdel(&room[hashcodes->hash_code]->link->name);
				free(room[hashcodes->hash_code]->link);
				room[hashcodes->hash_code]->link = tmp;
			}
			ft_strdel(&room[hashcodes->hash_code]->name);
			free(room[hashcodes->hash_code]);
			room[hashcodes->hash_code] = tmp2;
		}
		free(hashcodes);
		hashcodes = tmp1;
	}
	free(farm);
}

void	print_valid_data(t_farm *farm, t_room **room, char *argv)
{
	int			link;

	link = 0;
	farm->fd = open(argv, O_RDONLY);
	while (get_next_line(farm->fd, &farm->line) == 1)
	{
		if (!ft_strcmp("##start", farm->line))
			mark_room(farm->fd, room, &farm->line, 's');
		else if (!ft_strcmp("##end", farm->line))
			mark_room(farm->fd, room, &farm->line, 'e');
		else if (farm->line[0] == '#' && farm->line[1] == '#')
		{
			ft_strdel(&farm->line);
			continue ;
		}
		if (islink(farm->line))
			link = 1;
		if (link == 1 && isroom(farm->line))
		{
			ft_strdel(&farm->line);
			break ;
		}
		ft_printf("%s\n", farm->line);
		ft_strdel(&farm->line);
	}
}

int		main(int argc, char **argv)
{
	t_farm		*farm;
	t_room		**room;
	t_hashcodes	*hashcodes;

	hashcodes = NULL;
	if (argc == 2)
	{
		if (!(farm = (t_farm *)ft_memalloc(sizeof(t_farm))) ||
			!(room = (t_room **)malloc(sizeof(t_room) * 100136400)))
			exit(0);
		farm->fd = open(argv[1], O_RDONLY);
		if (farm->fd < 0)
		{
			write(2, "ERROR\n", 6);
			exit(0);
		}
		if (validation(room, farm, &hashcodes))
			print_valid_data(farm, room, argv[1]);
		else
			write(2, "ERROR\n", 6);
		free_all_structs(hashcodes, room, farm);
		exit(1);
	}
	write(2, "ERROR\n", 6);
	return (0);
}
