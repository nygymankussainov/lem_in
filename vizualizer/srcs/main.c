/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:45:43 by hfrankly          #+#    #+#             */
/*   Updated: 2019/10/09 21:47:35 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

int		ft_array_size(char **arr)
{
	int		count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}

int		main(int argc, char **argv)
{
	t_farm		*farm;

	farm = NULL;
	if (argc == 2 && (farm = (t_farm *)ft_memalloc(sizeof(t_farm)))
		&& (farm->size = count_room_viz(argv[1])))
	{
		if (!(farm->h_tab = (t_hash_tab *)ft_memalloc(sizeof(t_hash_tab)
			* (farm->size * 4))))
			exit(0);
		farm->fd = open("input_data", O_RDONLY);
		if ((farm->ret = validation(farm->h_tab, farm, &farm->hashcodes)) >= 0)
			vizualizer(farm);
		else
			write(2, "ERROR\n", 6);
		exit(1);
	}
	if (!farm->size)
		free(farm);
	write(2, "ERROR\n", 6);
	return (0);
}
