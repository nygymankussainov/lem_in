/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 14:20:12 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/19 21:50:29 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lem_in.h"

int		ft_reverse_shortest_path(t_farm *farm, int pathnbr)
{
	t_room	*tmproom;
	t_link	*link;

	tmproom = farm->endroom;
	while (tmproom != farm->startroom)
	{
		link = tmproom->link;
		while (link && link->room != tmproom->prev)
			link = link->next;
		if (link == NULL)
			return (0);
		link->weight = -1;
		link = tmproom->prev->link;
		while (link && link->room != tmproom)
			link = link->next;
		if (link == NULL)
			return (0);
		link->lock = 1;
		ft_printf("%s-", tmproom->name);
		tmproom->pathnbr = pathnbr;
		if (tmproom->induplicate || tmproom->outduplicate)
		{
			tmproom->parent->in->pathpart++;
			tmproom->parent->out->pathpart++;
		}
		else
			tmproom->pathpart++;
		tmproom = tmproom->prev;
	}
	ft_putchar('\n');
	return (1);
}
