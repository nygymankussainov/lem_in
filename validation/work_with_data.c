/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 15:03:04 by hfrankly          #+#    #+#             */
/*   Updated: 2019/08/30 15:33:17 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	mark_room(t_farm *farm, t_hash_tab *h_tab, char c)
{
	int		i;
	char	*name;
	t_room	*tmp;

	i = 0;
	ft_strdel(&farm->line);
	get_next_line(farm->fd, &farm->line);
	while (farm->line[i] != ' ')
		i++;
	name = ft_strndup(farm->line, i);
	i = hash_func(name, farm->size);
	tmp = h_tab[i].room;
	if (tmp)
		while (tmp)
		{
			if (!ft_strcmp(tmp->name, name))
				break ;
			tmp = tmp->next;
		}
	tmp->status = c;
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

void	print_valid_data(t_farm *farm, t_hash_tab *h_tab, char *argv)
{
	int			link;

	link = 0;
	farm->fd = open(argv, O_RDONLY);
	while (get_next_line(farm->fd, &farm->line) == 1)
	{
		if (!ft_strcmp("##start", farm->line))
			mark_room(farm, h_tab, 's');
		else if (!ft_strcmp("##end", farm->line))
			mark_room(farm, h_tab, 'e');
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
