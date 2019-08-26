/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:40:48 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/26 13:21:59 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	write_hashcode_in_struct(int hash, t_hashcodes **hashcodes)
{
	t_hashcodes	*new;

	if (*hashcodes)
	{
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

int		hash_func(char *name)
{
	int		i;
	int		g;
	int		hash;

	g = 28;
	hash = 0;
	i = 0;
	while (name[i] && i != 5)
		hash = hash * g + name[i++];
	return (hash);
}
