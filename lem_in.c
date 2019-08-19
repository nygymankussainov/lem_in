/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:04:16 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/19 19:51:46 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(int argc, char **argv)
{
	t_farm	*farm;
	int		fd;
	char	*line;
	t_room	**room;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (!(farm = (t_farm *)ft_memalloc(sizeof(t_farm))))
			return (0);
		if (validation(fd, farm, 0, &line))
		{
			hash_table(farm, room);
			ft_printf("%s", farm->output);
		}
		else
			write(2, "ERROR\n", 6);
		free(farm->output);
		free(farm->start);
		free(farm->end);
		free(farm->coords);
		free(farm->room_name);
		free(farm->link);
		free(farm);
		return (1);
	}
	write(2, "ERROR\n", 6);
	return (0);
}
