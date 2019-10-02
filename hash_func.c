/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:40:48 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/02 15:56:40 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		count_room(t_farm *farm)
{
	int		size;
	char	*line;

	farm->fd = 0;
	farm->newfd = open("tmpfd", O_CREAT | O_TRUNC | O_RDWR, S_IWRITE | S_IREAD);
	size = 0;
	if (farm->fd < 0 || farm->newfd < 0)
	{
		ft_putstr("heeelllooooo");
		return (0);
	}
	while (get_next_line(farm->fd, &line) == 1)
	{
		ft_putendl_fd(line, farm->newfd);
		if (isroom(line))
			size++;
		ft_strdel(&line);
	}
	close(farm->newfd);
	return (size);
}

void	write_hashcode_in_struct(int hash, t_hashcodes **hashcodes)
{
	t_hashcodes	*tmp;
	t_hashcodes	*new;

	tmp = *hashcodes;
	if (*hashcodes)
	{
		while (tmp)
		{
			if (hash == tmp->hash_code)
				return ;
			tmp = tmp->next;
		}
		if (!(new = (t_hashcodes *)ft_memalloc(sizeof(t_hashcodes))))
			return ;
		new->next = *hashcodes;
		new->hash_code = hash;
		*hashcodes = new;
	}
	else
	{
		if (!(*hashcodes = (t_hashcodes *)ft_memalloc(sizeof(t_hashcodes))))
			return ;
		(*hashcodes)->hash_code = hash;
		(*hashcodes)->next = NULL;
	}
}

int		hash_func(char *name, int size)
{
	int		i;
	int		hash;

	hash = 0;
	i = 0;
	while (name[i])
		hash += name[i++];
	return (hash % (size * 4));
}
