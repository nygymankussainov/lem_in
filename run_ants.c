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

// void	push_ants_to_end(t_path *path, int i)
// {
// 	t_queue	*q_path;
// 	int		tmp1;
// 	int		tmp2;

// 	q_path = path[i].queue;
// 	tmp1 = -1;
// 	while (q_path->next && q_path->next->room->antnbr < 0)
// 		q_path = q_path->next;
// 	if (q_path->next)
// 		tmp1 = q_path->next->room->antnbr;
// 	// if (q_path->room->antnbr < 0)
// 	// 	return ;
// 	if (q_path->next && q_path->next->room->status && q_path->room->antnbr >= 0)
// 	{
// 		q_path->next->room->antnbr += 1;
// 		ft_printf("L%d-%s ", q_path->room->antnbr, q_path->next->room->name);
// 	}
// 	else
// 	{
// 		if (q_path->next && !q_path->next->room->status)
// 			q_path->next->room->antnbr = q_path->room->antnbr;
// 		if (q_path->next && q_path->next->room->antnbr >= 0)
// 			ft_printf("L%d-%s ", q_path->next->room->antnbr, q_path->next->room->name);
// 	}
// 	q_path->room->antnbr = -1;
// 	q_path = q_path->next;
// 	tmp2 = tmp1;
// 	while (q_path && q_path->next && tmp1 >= 0)
// 	{
// 		if (q_path->next->room->status)
// 		{
// 			q_path->next->room->antnbr += tmp2 < 0 ? 0 : 1;
// 			if (tmp2 >= 0)
// 				ft_printf("L%d-%s ", tmp2, q_path->next->room->name);
// 			break ;
// 		}
// 		else
// 			tmp2 = q_path->next->room->antnbr;
// 		q_path->next->room->antnbr = tmp1;
// 		if (q_path->next->room->antnbr >= 0)
// 			ft_printf("L%d-%s ", q_path->next->room->antnbr, q_path->next->room->name);
// 		q_path = q_path->next;
// 		tmp1 = tmp2;
// 	}
// }

// void	push_ants_from_start(t_path *path, int i, int ant)
// {
// 	t_queue	*q_path;
// 	int		tmp1;
// 	int		tmp2;

// 	q_path = path[i].queue;
// 	tmp2 = 0;
// 	if (q_path->room->antnbr < 0)
// 	{
// 		q_path->room->antnbr = ant;
// 		ft_printf("L%d-%s ", q_path->room->antnbr, q_path->room->name);
// 	}
// 	else
// 	{
// 		if (q_path->next)
// 		{
// 			tmp1 = q_path->next->room->antnbr;
// 			if (q_path->next->room->status == 'e')
// 			{
// 				q_path->next->room->antnbr++;
// 				ft_printf("L%d-%s ", q_path->room->antnbr, q_path->next->room->name);
// 			}
// 			else
// 				q_path->next->room->antnbr = q_path->room->antnbr;
// 		}
// 		q_path->room->antnbr = ant;
// 		ft_printf("L%d-%s ", q_path->room->antnbr, q_path->room->name);
// 		if (q_path->next && q_path->next->room->status != 'e')
// 			ft_printf("L%d-%s ", q_path->next->room->antnbr, q_path->next->room->name);
// 		q_path = q_path->next;
// 		while (q_path && q_path->next && tmp1 != -1 && tmp2 != -1)
// 		{
// 			if (q_path->next->room->status)
// 			{
// 				q_path->next->room->antnbr++;
// 				ft_printf("L%d-%s ", tmp1, q_path->next->room->name);
// 			}
// 			else
// 			{
// 				tmp2 = q_path->next->room->antnbr;
// 				q_path->next->room->antnbr = tmp1;
// 				ft_printf("L%d-%s ", q_path->next->room->antnbr, q_path->next->room->name);
// 			}
// 			q_path = q_path->next;
// 			if (!q_path->next)
// 				break ;
// 			tmp1 = q_path->next->room->antnbr;
// 			q_path->next->room->antnbr = tmp2 >= 0 ? tmp2 : q_path->next->room->antnbr;
// 			if (tmp2 >= 0)
// 			{
// 				ft_printf("L%d-%s ", q_path->next->room->antnbr, q_path->next->room->name);
// 				q_path = q_path->next;
// 			}
// 		}
// 	}
// }

int		expression(t_path *path, int i)
{
	int		curr;
	int		result;

	curr = i;
	result = 0;
	while (i > 0)
	{
		i--;
		result += path[curr].steps - path[i].steps;
	}
	return (result);
}

int		issend(t_path *path, int ant, int i)
{
	if (ant >= expression(path, i))
		return (1);
	return (0);
}

int		ants_left_in_path(t_path path)
{
	t_queue		*q_path;

	q_path = path.queue;
	while (q_path)
	{
		if (q_path->room->antnbr >= 0 && q_path->room->status != 'e')
			return (1);
		q_path = q_path->next;
	}
	return (0);
}

void	run(t_farm *farm, int size, t_path *path)
{
	int		ant;
	int		i;
	int		tmp;
	int		sp;

	ant = 0;
	tmp = -1;
	sp = 0;
	while (ant < farm->ants)
	{
		i = 0;
		while (i < size)
		{
			if (!issend(path, farm->ants - ant, i))
			{
				if (ants_left_in_path(path[i]))
					tmp = i;
				else
					size = i;
			}
			else
				ant = push_ants_from_start(path, i, ant, sp);
			if (tmp >= 0)
			{
				push_ants_to_end(path, tmp, sp);
				tmp = -1;
			}
			sp = 1;
			i++;
			if (i >= size || ant >= farm->ants)
			{
				if (i >= size)
				{
					ft_printf("\n");
					sp = 0;
				}
				// else
				// 	ft_printf(" ");
				break ;
			}
			// else
			// 	ft_printf(" ");
		}
	}
	while (farm->endroom->antnbr + 1 != farm->ants)
	{
		if (i >= size)
			i = 0;
		while (i < size)
		{
			sp = push_ants_to_end(path, i, sp);
			i++;
			if (farm->endroom->antnbr + 1 == farm->ants)
				break ;
		}
		ft_printf("\n");
		sp = 0;
	}
}

void	run_ants(t_farm *farm)
{
	t_queue	*queue;
	t_queue	*last;
	t_path	*path;
	int		i;

	queue = NULL;
	last = NULL;
	i = count_paths(queue, farm->startroom, last, farm);
	if (!(path = (t_path *)ft_memalloc(sizeof(t_path) * i)))
		exit(0);
	unvisit_rooms(farm, 0);
	count_steps(queue, farm->startroom, last, path);
	sort_paths(path, i);
	unvisit_rooms(farm, 0);
	reindex_paths(queue, farm->startroom, path);
	sort_arr_path(path, i);
	unvisit_rooms(farm, 0);
	create_queue_of_paths(queue, path, farm->startroom, i);
	unvisit_rooms(farm, 2);
	run(farm, i, path);
	free(path);
}
