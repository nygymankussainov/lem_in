/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ant.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 17:57:58 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/12 18:27:23 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_lock(t_room *room, t_link *link)
{
	t_room	*room_tmp;
	t_link	*link_tmp;

	room_tmp = link->room;
	link_tmp = room_tmp->link;
	if (!link->lock)
		return (0);
	while (link_tmp && link_tmp->room->name != room->name)
	{
		link_tmp = link_tmp->next;
		if (!link_tmp)
			link_tmp = room_tmp->outroom ? room_tmp->outroom->link : link_tmp;
	}
	if (link_tmp && !link_tmp->lock)
		return (1);
	return (0);
}

// void	run(t_farm *farm, int size, t_path *path)
// {
// 	char	**result;
// 	t_link	*link;
// 	t_room	*room;
// 	int		i;

// 	room = farm->startroom;
// 	i = 0;
// 	result = NULL;
// 	while (room)
// 	{
// 		room = room->outroom ? room->outroom : room;
// 		link = room->link;
// 		while (link)
// 		{
// 			if (!link->room->visited && link->room->path == i && check_lock(room, link))
// 			{
// 				link->room->visited = 1;
// 				if (!result)
// 				result = ;
// 			}
// 			link = link->next;
// 		}
// 	}
// }

int		count_paths(t_queue *queue, t_room *room, t_queue *last, t_farm *farm)
{
	t_link	*link;
	int		i;
	int		j;

	i = 0;
	j = 0;
	enqueue(&queue, room, &last);
	unvisit_rooms(farm, 1);
	while (queue)
	{
		room = room->outroom ? room->outroom : room;
		link = room->link;
		while (link)
		{
			if (!link->room->visited && check_lock(room, link))
			{
				if (!link->room->status)
					enqueue(&queue, link->room, &last);
				link->room->visited = link->room-> status != 'e' ? 1 : link->room->visited;
				if (room->status == 's')
					link->room->dist = j;
				else if (!link->room->status)
					link->room->dist = room->dist;
				if (link->room->inroom)
					link->room->inroom->dist = link->room->dist;
				else if (link->room->outroom)
					link->room->outroom->dist = link->room->dist;
				if (link->room->status == 'e')
					i++;
				if (room->status != 's')
					break ;
				j++;
			}
			link = link->next;
		}
		dequeue(&queue);
		room = queue ? queue->room : room;
	}
	return (i);
}

void	count_steps(t_queue *queue, t_room *room, t_queue *last, t_path *path)
{
	t_link	*link;

	queue = NULL;
	last = NULL;
	enqueue(&queue, room, &last);
	while (queue)
	{
		room = room->outroom ? room->outroom : room;
		link = room->link;
		while (link)
		{
			if (!link->room->visited && check_lock(room, link))
			{
				if (!link->room->status)
				{
					enqueue(&queue, link->room, &last);
					path[link->room->dist].steps += !path[link->room->dist].steps ? 1 : 0;
					path[link->room->dist].steps++;
					path[link->room->dist].index = link->room->dist;
				}
				link->room->visited = link->room-> status != 'e' ? 1 : link->room->visited;
				if (room->status != 's')
					break ;
			}
			link = link->next;
		}
		dequeue(&queue);
		room = queue ? queue->room : room;
	}
}

void	reindex_paths(t_queue *queue, t_room *room, t_path *path)
{
	t_link	*link;
	t_queue *last;
	int		i;

	queue = NULL;
	last = NULL;
	enqueue(&queue, room, &last);
	i = 0;
	while (queue)
	{
		room = room->outroom ? room->outroom : room;
		link = room->link;
		while (link)
		{
			if (!link->room->visited && check_lock(room, link))
			{
				if (!link->room->status)
				{
					enqueue(&queue, link->room, &last);
					if (room->status == 's' && link->room->dist == i)
					{
						link->room->path = path[i].index;
						i++;
					}
					else
						link->room->path = room->path;
					if (link->room->inroom)
						link->room->inroom->path = link->room->path;
					else if (link->room->outroom)
						link->room->outroom->path = link->room->path;
				}
				link->room->visited = link->room-> status != 'e' ? 1 : link->room->visited;
				if (room->status != 's')
					break ;
			}
			link = link->next;
		}
		dequeue(&queue);
		room = queue ? queue->room : room;
	}
}

void	sort_arr_path(t_path *path, int size)
{
	int		i;
	int		j;
	t_path	tmp;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (path[j].index == i)
				break ;
			j++;
		}
		tmp = path[i];
		path[i] = path[j];
		path[j] = tmp;
		i++;
	}
}

void	create_queue_of_paths(t_queue *queue, t_path *path, t_room *room, int size)
{
	t_link	*link;
	t_queue	*last1;
	t_queue	*last2;
	t_room	*start;
	int		i;

	i = 0;
	start = room;
	while (i < size)
	{
		queue = NULL;
		last1 = NULL;
		last2 = NULL;
		room = start;
		enqueue(&queue, room, &last1);
		while (queue)
		{
			room = room->outroom ? room->outroom : room;
			link = room->link;
			while (link)
			{
				if ((link->room->path == i || link->room->status == 'e') && !link->room->visited && check_lock(room, link))
				{
					// if (room->status == 's')
					// 	enqueue(&path[link->room->path].queue, room, &last2);
					if (!link->room->status)
					{
						enqueue(&queue, link->room, &last1);
						enqueue(&path[link->room->path].queue, link->room, &last2);
					}
					else
						enqueue(&path[room->path].queue, link->room, &last2);
					if (link->room->status != 'e')
					{
						last2->index = path[link->room->path].index;
						last2->steps = path[link->room->path].steps;
					}
					link->room->visited = link->room-> status != 'e' ? 1 : link->room->visited;
					if (room->status != 's')
						break ;
				}
				link = link->next;
			}
			dequeue(&queue);
			room = queue ? queue->room : room;
		}
		i++;
	}
}

void	run_ants(t_farm *farm)
{
	t_queue	*queue;
	t_queue	*last;
	t_path	*path;
	t_ant	*ant;
	int		i;

	queue = NULL;
	last = NULL;
	i = count_paths(queue, farm->startroom, last, farm);
	if (!(ant = (t_ant *)ft_memalloc(sizeof(t_ant) * farm->ants)) ||
		!(path = (t_path *)ft_memalloc(sizeof(t_path) * i)))
		exit(0);
	unvisit_rooms(farm, 0);
	count_steps(queue, farm->startroom, last, path);
	sort_paths(path, i);
	unvisit_rooms(farm, 0);
	reindex_paths(queue, farm->startroom, path);
	sort_arr_path(path, i);
	unvisit_rooms(farm, 0);
	create_queue_of_paths(queue, path, farm->startroom, i);
	i = 0;
	while (i < farm->ants)
	{
		ant[i].antnbr = i;
		ant[i++].srcroom = farm->startroom;
	}
	unvisit_rooms(farm, 0);
	free(ant);
	free(path);
	// run(farm, i, path);
}
