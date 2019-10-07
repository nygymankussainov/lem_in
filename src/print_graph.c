/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:53:35 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/04 21:24:56 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_list(t_path *path)
{
	t_queue	*list;
	int		i;
	int		end;
	int		j;

	i = 0;
	end = 0;
	while (i < path->size)
	{
		list = path[i].list;
		while (list)
		{
			if (list->room->status == 'e')
				end++;
			// printf("%s", list->room->name);
			// if (list->room->out)
			// 	printf("out");
			// else if (list->room->in)
			// 	printf("in");
			// printf("-");
			// if (list->prev)
			// {
			// 	printf("list->prev %s", list->prev->room->name);
			// 	if (list->prev->room->out)
			// 		printf("out");
			// 	else if (list->prev->room->in)
			// 		printf("in");
			// }
			// if (list->room->prev)
			// {
			// 	printf("\n");
			// 	printf("room->prev %s", list->room->prev->name);
			// 	if (list->room->prev->out)
			// 		printf("out");
			// 	else if (list->room->prev->in)
			// 		printf("in");
			// }
			list = list->next;
		}
		// printf("\n");
		i++;
		// if (i >= path->size)
		// {
		// 	if (path->next)
		// 	{
		// 		end = 0;
		// 		path = path->next;
		// 		i = 0;
		// 	}
		// }
	}
	j = 0;
	while (j < path->size)
	{
		printf("steps: %d\n", path[j].steps);
		j++;
	}
	printf("size: %d\n", path->size);
	printf("end: %d\n", end);
}

void	print_graph(t_farm *farm)
{
	t_link	*link;
	t_queue	*queue;
	t_queue	*last;
	t_room	*room;

	unvisit_rooms(farm, 0);
	queue = NULL;
	last = NULL;
	room = farm->startroom;
	enqueue(&queue, room, &last);
	while (queue)
	{
		link = room->link;
		while (link)
		{
			if (!link->room->visited)
				enqueue(&queue, link->room, &last);
			// if (room->prev)
			// 	printf("%s is prev of ", room->prev->name);
			if (room->dup)
			{
				if (room->in)
					printf("%sin ", room->name);
				else if (room->out)
					printf("%sout ", room->name);
			}
			else
				printf("%s ", room->name);
			if (!link->lock)
				printf("- ");
			else
				printf("lock - ");
			if (link->room->dup)
			{
				if (link->room->in)
					printf("%sin", link->room->name);
				else if (link->room->out)
					printf("%sout", link->room->name);
			}
			else
				printf("%s", link->room->name);
			printf(" %d\n", link->weight);
			link = link->next;
		}
		room->visited = 1;
		dequeue(&queue);
		room = queue ? queue->room : room;
	}
}
