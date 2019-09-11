/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:45:43 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/11 15:15:15 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

int		main(int argc, char **argv)
{
	t_farm		*farm;
	t_hash_tab	*h_tab;
	t_hashcodes	*hashcodes;

	hashcodes = NULL;
	if ((farm = (t_farm *)ft_memalloc(sizeof(t_farm))) && argc == 2
		&& (farm->size = count_room(argv[1])))
	{
		if (!(h_tab = (t_hash_tab *)ft_memalloc(sizeof(t_hash_tab )
			* (farm->size * 4))))
			exit(0);
		farm->fd = open(argv[1], O_RDONLY);
		if (validation(h_tab, farm, &hashcodes))
			print_valid_data(farm, argv[1]);
		else
		{
			write(2, "ERROR\n", 6);
			exit(0);
		}
		farm->h_tab = h_tab;
		farm->hashcodes = hashcodes;
		vizualizer(farm);
		free_all_structs(hashcodes, h_tab, farm);
		return(1);
	}
	if (!farm->size)
		free(farm);
	write(2, "ERROR\n", 6);
	return (0);
}

