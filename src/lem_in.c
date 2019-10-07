/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:04:16 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/07 13:02:47 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "lem_in.h"

int		main(void)
{
	t_farm		*farm;
	t_hash_tab	*h_tab;
	t_hashcodes	*hashcodes;
	t_path		*path;
	int			ret;

	hashcodes = NULL;
	path = NULL;
	if ((farm = (t_farm *)ft_memalloc(sizeof(t_farm)))
		&& (farm->size = count_room()))
	{
		if (!(h_tab = (t_hash_tab *)ft_memalloc(sizeof(t_hash_tab)
			* (farm->size * 4))))
			exit(0);
		farm->fd = open("input_data", O_RDONLY);
		if (validation(h_tab, farm, &hashcodes) && ((ret = bfs(farm, &path)) >= 0))
		{
			while (ret)
				if (!bellman_ford(farm, path) || !(ret = create_paths(farm, &path)))
					break ;
			print_valid_data(farm);
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
