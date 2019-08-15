/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:04:16 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/15 19:43:30 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(int argc, char **argv)
{
	t_farm	*farm;
	int		fd;

	fd = argc == 2 ? open(argv[1], O_RDONLY) : 0;
	if (!(farm = (t_farm *)ft_memalloc(sizeof(t_farm))))
		return (0);
	if (argc > 2 || !validation(fd, farm))
	{
		write(2, "ERROR\n", 6);
		free(farm->output);
		farm->output = NULL;
		free(farm->room);
		free(farm);
		farm = NULL;
		return (0);
	}
	return (0);
}
