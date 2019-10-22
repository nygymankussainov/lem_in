/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_linkwith_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 21:57:00 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/22 14:29:01 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** In link_back() funcion we check if we have in
** two or more paths the same link.
** For expample: we have two paths: A-E-D-H and
** A-B-C-D-E-H. The same link is E-D and D-E.
** That is what we are looking for in this function
** to delete it.
*/

int		link_back(t_room *room, t_queue *list)
{
	t_queue	*linkwith;

	linkwith = list;
	while (linkwith)
	{
		if (linkwith->room == room && list->room->status != 'e')
			return (1);
		linkwith = linkwith->next;
	}
	return (0);
}

void	linkwith_start(t_room *room1, t_room *room2)
{
	t_queue	*new;

	if (!(new = (t_queue *)ft_memalloc(sizeof(t_queue))))
		exit(0);
	if (room1->status == 's')
	{
		new->room = room2;
		new->next = room1->linkwith;
		room1->linkwith = new;
	}
}

void	delete_linkwith_rooms(t_queue *list)
{
	t_queue	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

/*
** In create_linkwith_list() function we 
** for every room that belong to new found path
** create a list of rooms that the link with.
** For expample: if the path is A-E-D-H,
** room A will have a list with room E,
** room E will have a list with room D,
** and room D will have a list with room H.
** If the second found path is A-B-C-D-E-F-G-H,
** the room A will have a list of rooms B and E,
** room D will now have E and H, room E will have
** a list of F and D, and so on.
*/

void	create_linkwith_list(t_room *room1, t_room *room2)
{
	if (!room1->linkwith)
	{
		if (!(room1->linkwith = (t_queue *)ft_memalloc(sizeof(t_queue))))
			exit(0);
		room1->linkwith->room = room2;
	}
	else
	{
		if (room1->status == 's')
			linkwith_start(room1, room2);
		else
		{
			if (link_back(room1, room2->linkwith))
				return ;
			delete_linkwith_rooms(room1->linkwith);
			room1->linkwith = NULL;
			create_linkwith_list(room1, room2);
		}
	}
}

void	fill_room_linkwith(t_path *path)
{
	t_queue	*list;

	list = path->list;
	while (list && list->next)
	{
		create_linkwith_list(list->room, list->next->room);
		list = list->next;
	}
}
