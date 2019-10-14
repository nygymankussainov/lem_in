/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:40:48 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/14 19:51:04 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int		count_room(char c)
{
	int		size;
	char	*line;
	int		fd1;
	int		fd2;

	fd1 = 0;
	fd2 = 0;
	if (c == 'v')
		fd1 = open("input_data", O_RDONLY);
	else
		fd2 = open("input_data", O_CREAT | O_TRUNC
			| O_RDWR, S_IWRITE | S_IREAD);
	size = 0;
	while (get_next_line(fd1, &line) == 1)
	{
		if (line && fd2)
			ft_putendl_fd(line, fd2);
		if (line && isroom(line))
			size++;
		ft_strdel(&line);
	}
	close(fd1);
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
