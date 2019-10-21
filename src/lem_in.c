/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:04:16 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/21 22:11:56 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_farm		*farm;

	if ((farm = (t_farm *)ft_memalloc(sizeof(t_farm)))
		&& (farm->size = count_room('a')))
	{
		if (!(farm->h_tab = (t_hash_tab *)ft_memalloc(sizeof(t_hash_tab)
			* (farm->size * 4))))
			exit(0);
		farm->fd = open("input_data", O_RDONLY);
		if ((farm->ret = validation(farm->h_tab, farm, &farm->hashcodes)) >= 0)
		{
			while (farm->ret)
				if (!bellman_ford(farm, farm->path)
					|| !(farm->ret = create_paths(farm, &farm->path)))
					break ;
			run_ants(farm, farm->path);
		}
		else
			write(2, "ERROR\n", 6);
		exit(1);
	}
	if (!farm->size)
		free(farm);
	write(2, "ERROR\n", 6);
	return (0);
}

// int		main(int argc, char **argv)
// {
// 	t_farm		*farm;

// 	if ((farm = (t_farm *)ft_memalloc(sizeof(t_farm))) && argc == 2
// 		&& (farm->size = count_room(argv[1])))
// 	{
// 		if (!(farm->h_tab = (t_hash_tab *)ft_memalloc(sizeof(t_hash_tab)
// 			* (farm->size * 4))))
// 			exit(0);
// 		farm->fd = open(argv[1], O_RDONLY);
// 		if ((farm->ret = validation(farm->h_tab, farm, &farm->hashcodes)) >= 0)
// 		{
// 			while (farm->ret)
// 			{
// 				if (!bellman_ford(farm, farm->path)
// 					|| !(farm->ret = create_paths(farm, &farm->path)))
// 					break ;
// 				if (farm->path->size == 10)
// 					todot(farm->path, "map_loop2");
// 				// print_path(farm->path);
// 				// printf("\n\n\n\n");
// 			}
// 			// run_ants(farm, farm->path);
// 		}
// 		else
// 			write(2, "ERROR\n", 6);
// 		exit(1);
// 	}
// 	if (!farm->size)
// 		free(farm);
// 	write(2, "ERROR\n", 6);
// 	return (0);
// }
