/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpful_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:06:19 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/29 16:06:42 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_links(t_hashcodes *hashcodes, t_hash_tab *h_tab)
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
				printf("%s-%s\n", h_tab[hashcodes->hash_code].room->name,
					h_tab[hashcodes->hash_code].room->link->room->name);
				h_tab[hashcodes->hash_code].room->link = tmp;
			}
			h_tab[hashcodes->hash_code].room = tmp2;
		}
		hashcodes = tmp1;
	}
}

int		is_room_exist(int hash, t_hashcodes *hashcodes)
{
	while (hashcodes)
	{
		if (hash == hashcodes->hash_code)
			return (1);
		hashcodes = hashcodes->next;
	}
	return (0);
}
