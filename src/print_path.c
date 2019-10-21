/*  */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 14:41:35 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/18 14:42:07 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/*  */

#include "lem_in.h"

void	print_path(t_path *path)
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
