/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:04:16 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/12 19:36:59 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "lem_in.h"

int		main(int argc, char **argv)
{
	t_farm		*farm;
	t_hash_tab	*h_tab;
	t_hashcodes	*hashcodes;
	int			ret;

	hashcodes = NULL;
	if ((farm = (t_farm *)ft_memalloc(sizeof(t_farm))) && argc == 2
		&& (farm->size = count_room(argv[1])))
	{
		if (!(h_tab = (t_hash_tab *)ft_memalloc(sizeof(t_hash_tab )
			* (farm->size * 4))))
			exit(0);
		farm->fd = open(argv[1], O_RDONLY);
		if (validation(h_tab, farm, &hashcodes) && ((ret = bfs(farm)) >= 0))
		{
			if (ret > 0)
				while (ret > 1)
				{
					ret--;
					if (!bellman_ford(farm))
						break ;
					if (!find_shortest_path(farm, ret) || ret <= 1)
						break ;
				}
			// print_valid_data(farm, argv[1]);
			unvisit_rooms(farm);
			run_ants(farm);
		}
		else
			write(2, "ERROR\n", 6);
		farm->h_tab = h_tab;
		farm->hashcodes = hashcodes;
		free_all_structs(hashcodes, h_tab, farm);
		exit(1);
	}
	if (!farm->size)
		free(farm);
	write(2, "ERROR\n", 6);
	return (0);
}
