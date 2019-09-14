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

// void	run(t_queue *queue, t_farm *farm, int size, t_path *path)
// {
// 	t_link	*link;
// 	t_queue	*last;
// 	t_room	*room;
// 	int		k;

// 	room = queue->room;
// 	last = queue;
// 	k = 0;
// 	while (queue)
// 	{
// 		room = room->outroom ? room->outroom : room;
// 		link = room->link;
// 		while (link)
// 		{
// 			if (!link->room->visited && check_lock(room, link))
// 			{
// 				enqueue(&queue, link->room, &last);
// 				link->room->visited = link->room-> status != 'e' ? 1 : link->room->visited;
// 				if (link->room->status == 'e')
// 					k++;
// 				if (room->status != 's')
// 					break ;
// 			}
// 			link = link->next;
// 		}
// 		dequeue(&queue);
// 		room = queue ? queue->room : room;
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
	unvisit_rooms(farm);
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
					link->room->path = j;
				else if (link->room->path < 0 && !link->room->status)
					link->room->path = room->path;
				if (link->room->inroom)
					link->room->inroom->path = link->room->path;
				else if (link->room->outroom)
					link->room->outroom->path = link->room->path;
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
					printf("path %d\n", link->room->path);
					path[link->room->path].steps += !path[link->room->path].steps ? 1 : 0;
					path[link->room->path].steps++;
					path[link->room->path].index = link->room->path;
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

void	ft_show_array(int *arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_printf("%d ", arr[i]);
		i++;
	}
	ft_putchar('\n');
}

int		*ft_path_into_array(t_path *path, int size)
{
	int		i;
	int		*array;

	i = 0;
	if (!(array = (int*)malloc(4 * size)))
		exit(0);
	while (i < size)
	{
		array[i] = path[i].steps;
		i++;
	}
	return (array);
}

void	ft_array_to_path(int *array, t_path *path, int size)
{
	int		i;
	int		j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size && array[i] != path[j].steps)
			j++;
		path[j].index = i;
		i++;
	}
}

void	run_ants(t_farm *farm)
{
	t_queue	*queue;
	t_queue	*last;
	t_path	*path;
	int		*array;
	t_ant	*ant;
	int		i;
	int		size;

	queue = NULL;
	last = NULL;
	i = count_paths(queue, farm->startroom, last, farm);
	if (!(ant = (t_ant *)ft_memalloc(sizeof(t_ant) * farm->ants)) ||
		!(path = (t_path *)ft_memalloc(sizeof(t_path) * i)))
		exit(0);
	unvisit_rooms(farm);
	count_steps(queue, farm->startroom, last, path);
	
	size = i;
	i = 0;
	while (i < size)
	{
		ft_printf("%d %d\n", path[i].index, path[i].steps);
		i++;
	}
	ft_putchar('\n');

	array = ft_path_into_array(path, size);
	ft_qsort(array, size);
	ft_show_array(array, size);
	ft_array_to_path(array, path, size);

	i = 0;
	while (i < size)
	{
		ft_printf("%d %d\n", path[i].index, path[i].steps);
		i++;
	}
	i = 0;
	while (i < farm->ants)
	{
		ant[i].antnbr = i;
		ant[i++].srcroom = farm->startroom;
	}
	unvisit_rooms(farm);
	queue = NULL;
	last = NULL;
	enqueue(&queue, farm->startroom, &last);
	// run(queue, farm, i, path);
}
