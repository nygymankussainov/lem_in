/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:04:16 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/23 18:35:03 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "lem_in.h"

int		main(int argc, char **argv)
{
	t_farm		*farm;
	t_hash_tab	*h_tab;
	t_hashcodes	*hashcodes;
	t_path		*path;
	int			ret;

	hashcodes = NULL;
	path = NULL;
	if ((farm = (t_farm *)ft_memalloc(sizeof(t_farm))) && argc == 2
		&& (farm->size = count_room(argv[1])))
	{
		if (!(h_tab = (t_hash_tab *)ft_memalloc(sizeof(t_hash_tab )
			* (farm->size * 4))))
			exit(0);
		farm->fd = open(argv[1], O_RDONLY);
		if (validation(h_tab, farm, &hashcodes) && ((ret = bfs(farm, &path)) >= 0))
		{
			while (ret > 0)
			{
				if (!bellman_ford(farm, path))
					break ;
				if (!create_paths(farm, &path))
					break ;
				// ret = find_shortest_path(farm, &path, ret);
				// if (! || ret <= 1)
				// 	break ;
			}
			print_valid_data(farm, argv[1]);
			run_ants(farm, path);
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
