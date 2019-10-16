/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:53:35 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/15 15:53:28 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	print_list(t_path *path)
{
	t_queue	*list;
	int		i;

	i = 0;
	while (i < path->size)
	{
		list = path[i].list;
		while (list)
		{
			printf("%s", list->room->name);
			printf("-");
			list = list->next;
		}
		printf("\n");
		i++;
	}
}

void	todot(t_path *path, char *name)
{
	t_queue	*list;
	int		i;
	int		end;
	int		j;
	int		fd;

	name = ft_strjoin(name, "1.dot", 0, 0);
	fd = open(name, O_CREAT | O_TRUNC | O_RDWR, S_IWRITE | S_IREAD);
	ft_putstr_fd("digraph map\n", fd);
	ft_putstr_fd("{\n", fd);
	i = 0;
	end = 0;
	j = 0;
	while (i < path->size)
	{
		list = path[i].list;
		j = 0;
		while (list)
		{
			if (list->room->status == 'e')
				end++;
			if (j % 2 == 0)
				ft_putstr_fd("\t", fd);
			ft_putstr_fd(list->room->name, fd);
			if (j % 2 == 0)
				ft_putstr_fd("->", fd);
			else
			{
				ft_putstr_fd(" [color=red, style=bold];", fd);
				ft_putstr_fd("\n", fd);
				if (list->room->status != 'e')
				{
					ft_putstr_fd("\t", fd);
					ft_putstr_fd(list->room->name, fd);
					ft_putstr_fd("->", fd);
				}
				j++;
			}
			j++;
			list = list->next;
		}
		i++;
	}
	ft_putstr_fd("}\n", fd);
}

// void	print_graph(t_farm *farm)
// {
// 	t_link	*link;
// 	t_queue	*queue;
// 	t_queue	*last;
// 	t_room	*room;

// 	unvisit_rooms(farm, 0);
// 	queue = NULL;
// 	last = NULL;
// 	room = farm->startroom;
// 	enqueue(&queue, room, &last);
// 	while (queue)
// 	{
// 		link = room->link;
// 		while (link)
// 		{
// 			if (!link->room->visited)
// 				enqueue(&queue, link->room, &last);
// 			// if (room->prev)
// 			// 	ft_putstr_fd("%s is prev of ", room->prev->name);
// 			if (room->dup)
// 			{
// 				if (room->in)
// 					ft_putstr_fd("%sin ", room->name);
// 				else if (room->out)
// 					ft_putstr_fd("%sout ", room->name);
// 			}
// 			else
// 				ft_putstr_fd("%s ", room->name);
// 			if (!link->lock)
// 				ft_putstr_fd("- ");
// 			else
// 				ft_putstr_fd("lock - ");
// 			if (link->room->dup)
// 			{
// 				if (link->room->in)
// 					ft_putstr_fd("%sin", link->room->name);
// 				else if (link->room->out)
// 					ft_putstr_fd("%sout", link->room->name);
// 			}
// 			else
// 				ft_putstr_fd("%s", link->room->name);
// 			ft_putstr_fd(" %d\n", link->weight);
// 			link = link->next;
// 		}
// 		room->visited = 1;
// 		dequeue(&queue);
// 		room = queue ? queue->room : room;
// 	}
// }
