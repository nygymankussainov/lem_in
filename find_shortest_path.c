/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_shortest_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 18:38:35 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/11 19:53:16 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_count_paths(t_farm *farm)
{
	int		start;
	int		end;
	t_link  *link;

	end = 0;
	start = 0;
	link = farm->startroom->link;
	while (link)
	{
		link = link->next;
		start++;
	}
	link = farm->endroom->link;
	while (link)
	{
		end++;
		link = link->next;
	}
	return ((start < end) ? start : end);
}

void	ft_add_path(t_farm *farm, t_path *newpath)
{
	int		i;

	i = 0;
	if (farm->paths == NULL)
		farm->paths = (t_path**)ft_memalloc(sizeof(t_path*) * ft_count_paths(farm));
	while (farm->paths[i])
		i++;
	farm->paths[i] = newpath;
}

void	unvisit_rooms(t_farm *farm)
{
	t_hashcodes	*tmp;
	t_room		*room;

	tmp = farm->hashcodes;
	while (tmp)
	{
		room = farm->h_tab[tmp->hash_code].room;
		while (room)
		{
			room->visited = 0;
			if (room->dup)
				room->outroom->visited = 0;
			room = room->next;
		}
		tmp = tmp->next;
	}
}

void	manage_links(t_room *in, t_room *out)
{
	t_link	*linkin;
	t_link	*linkout;
	t_link	*tmp;

	if (!(linkin = (t_link *)ft_memalloc(sizeof(t_link))) ||
		!(tmp = (t_link *)ft_memalloc(sizeof(t_link))))
		exit(0);
	linkin->room = !in->prev->dup ? in->prev : in->prev->outroom;
	linkin->weight = -1;
	out->link = in->link;
	tmp->room = out;
	tmp->lock = 1;
	tmp->next = linkin;
	linkin = tmp;
	in->link = linkin;
	linkout = out->link;
	while (linkout)
	{
		if (linkout->room == in->prev)
		{
			linkout->room = in;
			linkout->weight = 0;
			linkout->lock = 0;
			break ;
		}
		linkout = linkout->next;
	}
}

void	create_dup_rooms(t_path *path)
{
	t_room	*in;
	t_room	*out;

	if (!(out = (t_room *)ft_memalloc(sizeof(t_room))))
		exit(0);
	in = path->room;
	in->dup = 1;
	in->in = 1;
	in->outroom = out;
	out->out = 1;
	out->dup = 1;
	out->inroom = in;
	out->name = in->name;
	out->x = in->x;
	out->y = in->y;
	out->dist = in->dist;
	out->prev = in;
	out->next = in->next;
	manage_links(in, out);
}

int		find_shortest_path(t_farm *farm, int ret)
{
	t_room	*room;
	t_path	*path;
	t_path	*new;
	t_path	*tmp;
	t_link	*locklink;

	room = farm->endroom;
	if (!(path = (t_path *)ft_memalloc(sizeof(t_path) * ret + 1)))
		exit(0);
	path->room = room;
	room = room->prev;
	if (room->status == 's')
		ret = 0;
	while (room)
	{
		if (!(new = (t_path *)ft_memalloc(sizeof(t_path))))
			exit(0);
		new->room = room;
		new->next = path;
		path = new;
		room = room->prev;
		locklink = path->room->link;
		while (locklink->room != path->next->room)
			locklink = locklink->next;
		locklink->lock = 1;
	}
	if (ret > 1)
	{
		tmp = path;
		while (tmp && tmp->room->status != 'e')
		{
			if (tmp->next->room->status == 'e')
				room = tmp->room;
			tmp = tmp->next;
			if (!tmp->room->dup && !tmp->room->status)
				create_dup_rooms(tmp);
			if (tmp->room->status == 'e')
			{
				locklink = tmp->room->link;
				while (locklink && locklink->room != room)
					locklink = locklink->next;
				if (locklink)
				{
					locklink->room = room->outroom;
					locklink->weight = -1;
				}
			}
		}
	}
	ft_add_path(farm, path);
	// while (path)
	// {
	// 	// printf("%s-", path->room->name);
	// }
	// printf("\n");
	// printf("%s\n", room->name);
	return (ret);
}
