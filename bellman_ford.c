/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:52:47 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/02 22:15:57 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	assign_inf_dist(t_farm *farm)
{
	t_hashcodes	*tmp;
	t_room		*room;

	tmp = farm->hashcodes;
	while (tmp)
	{
		room = farm->h_tab[tmp->hash_code].room;
		while (room)
		{
			room->dist = room->status != 's' ? INT_MAX : room->dist;
			if (room->outroom)
				room->outroom->dist = INT_MAX;
			room = room->next;
		}
		tmp = tmp->next;
	}
}

int		calculate_neg_dist(t_queue **queue, t_room *room, t_queue *last)
{
	t_link	*link;
	bool	change;
	int		ret;

	change = 0;
	ret = 0;
	while (*queue)
	{
		// if (!ft_strcmp((*queue)->room->name, "Uct9"))
		// 	ret = ret + 0;
		// if (!ft_strcmp((*queue)->room->name, "Qau9"))
		// 	ret = ret + 0;
		// if (!ft_strcmp((*queue)->room->name, "Idj9"))
		// 	ret = ret + 0;
		// if (!ft_strcmp((*queue)->room->name, "Oxs2"))
		// 	ret = ret + 0;
		// if (!ft_strcmp((*queue)->room->name, "Xta8"))
		// 	ret = ret + 0;
		// if (!ft_strcmp((*queue)->room->name, "Fmp9"))
		// 	ret = ret + 0;
		// if (!ft_strcmp((*queue)->room->name, "Rjg7"))
		// 	ret = ret + 0;
		// if (!ft_strcmp((*queue)->room->name, "Fqb9"))
		// 	ret = ret + 0;
		// if (!ft_strcmp((*queue)->room->name, "Wlx2"))
		// 	ret = ret + 0;
		// if (!ft_strcmp((*queue)->room->name, "Ebi3"))
		// 	ret = ret + 0;
		// if (!ft_strcmp((*queue)->room->name, "Sjz3"))
		// 	ret = ret + 0;
		// if (!ft_strcmp((*queue)->room->name, "Jdk5"))
		// 	ret = ret + 0;
		// if (!ft_strcmp((*queue)->room->name, "Fpy1"))
		// 	ret = ret + 0;
		// if (!ft_strcmp((*queue)->room->name, "D_i7"))
		// 	ret = ret + 0;
		// if (!ft_strcmp((*queue)->room->name, "Vhm4"))
		// 	ret = ret + 0;
		link = room->link;
		while (link && room->status != 'e')
		{
			if (link->room)
				ret = link->room->status == 'e' ? 1 : ret;
			if (!link->lock && !link->room->visited && link->room->status != 'e')
				enqueue(queue, link->room, &last);
			if (!link->lock && room->dist + link->weight < link->room->dist
				&& link->room->status != 's')
			{
				link->room->dist = room->dist + link->weight;
				// if (link->room->inroom)
				// {
				// 	link->room->inroom->dist = link->room->dist;
				// 	link->room->inroom->prev = room;
				// }
				// else if (link->room->outroom)
				// {
				// 	link->room->outroom->dist = link->room->dist;
				// 	link->room->outroom->prev = room;
				// }
				link->room->prev = room;
				change = 1;
			}
			link = link->next;
		}
		dequeue(queue);
		room->visited = 1;
		if (room->inroom)
			room->inroom->visited = 1;
		else if (room->outroom)
			room->outroom->visited = 1;
		room = *queue ? (*queue)->room : room;
	}
	ret = ret && change ? 2 : ret;
	return (ret);
}

int		bellman_ford(t_farm *farm, t_path *path)
{
	t_queue	*queue;
	t_queue	*last;
	int		i;
	int		ret;

	i = 0;
	queue = NULL;
	last = NULL;
	create_dup_rooms(path);
	// printf("AFTER CREATE_DUP_ROOMS\n");
	// print_graph(farm);
	// print_list(path);
	while (i < path->size)
		manage_direction(path + i++, 1); /* reverse (make directed from end to start) edges in path(s) */
	// printf("AFTER MANAGE_DIRECTON\n");
	// print_graph(farm);
	// print_list(path);
	assign_inf_dist(farm);
	i = 0;
	while (i++ < farm->room_count - 1)
	{
		unvisit_rooms(farm, 0);
		enqueue(&queue, farm->startroom, &last);
		ret = calculate_neg_dist(&queue, farm->startroom, last);
		if (ret == 1)
		{
			delete_dup_rooms(path);
			// printf("AFTER DELETE\n");
			// print_graph(farm);
			// print_list(path);
			return (1);
		}
		else if (!ret)
		{
			delete_dup_rooms(path);
			// printf("AFTER DELETE\n");
			// print_graph(farm);
			// print_list(path);
			return (0);
		}
	}
	delete_dup_rooms(path);
	return (1);
}
