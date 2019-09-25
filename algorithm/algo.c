/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 15:10:05 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/25 16:41:05 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	ft_make_room_inf(t_farm *farm)
{
	t_hashcodes	*hc;
	t_hash_tab	*ht;
	t_link		*link;
	t_room		*room;

	hc = farm->hashcodes;
	ht = farm->h_tab;
	while (hc)
	{
		room = ht[hc->hash_code].room;
		while (room)
		{
			if (room->in != NULL)
			{
				room->pathlength = 2147483637;
				room->in->pathlength = 2147483637;
				room->out->pathlength = 2147483637;
			}
			else
				room->pathlength = 2147483637;
			link = room->link;
			room = room->next;
		}
		hc = hc->next;
	}
	farm->startroom->pathlength = 0;
}

void	ft_bell_ford(t_farm *farm)
{
	t_link		*link;
	t_room		*room;
	t_room		**queue;
	int			iter;
	int			endqueue;
	int			i;
	bool		changes;

	i = 0;
	if (!is_free_path(farm))
		return ;
	ft_make_room_inf(farm);
	farm->room_count += farm->duplicate_count;
	if (!(queue = (t_room**)ft_memalloc(sizeof(t_room*) * farm->room_count * 2)))
		exit(0);
	while (i < farm->room_count)
	{
		iter = 0;
		endqueue = 1;
		queue[0] = farm->startroom;
		changes = false;
		while (iter < farm->room_count && iter < endqueue)
		{
			room = queue[iter];
			room->visited = true;
			link = room->link;
			while (link)
			{
				if (!link->lock && link->room->pathlength > room->pathlength + link->weight)
				{
					link->room->pathlength = room->pathlength + link->weight;
					link->room->prev = room;
					queue[endqueue] = link->room;
					changes = true;
					endqueue++;
				}
				link = link->next;
			}
			iter++;
		}
		unvisit_rooms(farm);
		if (changes == false)
		{
			break;
		}
		if (i == farm->room_count)
		{
			ft_printf("Cycle detected\n");
			exit(0);
		}
		i++;
	}
	free(queue);
	farm->room_count -= farm->duplicate_count;
}

void    lem_in(t_farm *farm)
{
	int		pathnbr;
	t_path	**pathes;
	t_path	*path;
	int		count;

	count = 0;
	pathnbr = 1;
	farm->duplicate_count = 0;
	while (pathnbr < 10)
	{
		if (!ft_reverse_shortest_path(farm, pathnbr))
			break ;
		ft_make_rooms_duplicates(farm);
    	ft_bell_ford(farm);
		pathnbr++;
	}
	ft_reverse_shortest_path(farm, pathnbr);
	ft_putendl("refresh");
	ft_refresh_graph(farm);
	unvisit_rooms(farm);
	ft_putendl("pathes");
	pathes = ft_pickout_pathes(farm, pathnbr);
	// output
	while (count < pathnbr)
	{
		path = pathes[count];
		while (path)
		{
			ft_printf("%s-", path->room->name);
			path = path->prev;
		}
		ft_putchar('\n');
		count++;
	}
	// ft_send_ants(farm, pathnbr);
}
