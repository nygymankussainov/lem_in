/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:04:16 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/09 20:51:50 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int		main(void)
{
	t_farm		*farm;

	if ((farm = (t_farm *)ft_memalloc(sizeof(t_farm)))
		&& (farm->size = count_room()))
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
