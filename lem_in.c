/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:04:16 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/02 13:21:08 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void	free_all_structs(t_hashcodes *hashcodes,
	t_hash_tab *h_tab, t_farm *farm)
{
	t_link		*tmp;
	t_hashcodes	*tmp1;
	t_room		*tmp2;

	while (hashcodes)
	{
		tmp1 = hashcodes->next;
		while (h_tab[hashcodes->hash_code].room)
		{
			tmp2 = h_tab[hashcodes->hash_code].room->next;
			while (h_tab[hashcodes->hash_code].room->link)
			{
				tmp = h_tab[hashcodes->hash_code].room->link->next;
				free(h_tab[hashcodes->hash_code].room->link);
				h_tab[hashcodes->hash_code].room->link = tmp;
			}
			ft_strdel(&h_tab[hashcodes->hash_code].room->name);
			free(h_tab[hashcodes->hash_code].room);
			h_tab[hashcodes->hash_code].room = tmp2;
		}
		free(hashcodes);
		hashcodes = tmp1;
	}
	free(farm);
}

void	print_valid_data(t_farm *farm, char *argv)
{
	int			link;

	link = 0;
	farm->fd = open(argv, O_RDONLY);
	while (get_next_line(farm->fd, &farm->line) == 1)
	{
		if (ft_strcmp("##start", farm->line) && ft_strcmp("##end", farm->line)
			&& farm->line[0] == '#' && farm->line[1] == '#')
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
	ft_printf("\n");
}

int		main(int argc, char **argv)
{
	t_farm		*farm;
	t_hash_tab	*h_tab;
	t_hashcodes	*hashcodes;

	hashcodes = NULL;
	if ((farm = (t_farm *)ft_memalloc(sizeof(t_farm))) && argc == 2
		&& (farm->size = count_room(argv[1])))
	{
		if (!(h_tab = (t_hash_tab *)ft_memalloc(sizeof(t_hash_tab )
			* (farm->size * 4))))
			exit(0);
		farm->fd = open(argv[1], O_RDONLY);
		if (validation(h_tab, farm, &hashcodes) && bfs(farm))
		{
			while (find_shortest_path(farm) == 1)
			{
				unvisit_rooms(farm);
				bfs(farm);
			}
			// print_valid_data(farm, argv[1]);
		}
		else
			write(2, "ERROR\n", 6);
		free_all_structs(hashcodes, h_tab, farm);
		exit(1);
	}
	if (!farm->size)
		free(farm);
	write(2, "ERROR\n", 6);
	return (0);
}
