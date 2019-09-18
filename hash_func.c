/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:40:48 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/18 17:51:51 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		count_room(char *argv)
{
	int		fd;
	int		size;
	char	*line;

	fd = open(argv, O_RDONLY);
	size = 0;
	if (fd <= 0)
		return (0);
	while (get_next_line(fd, &line) == 1)
	{
		if (isroom(line))
			size++;
		ft_strdel(&line);
	}
	close(fd);
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
