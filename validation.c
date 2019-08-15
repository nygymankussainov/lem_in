/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 16:04:51 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/15 16:21:20 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		validation(char *str)
{
	int		fd;
	char	*line;

	fd = open(str, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		
	}
}

int		main(int argc, char **argv)
{
	if (argc > 1)
	{
		if (!validation(argv[1]))
		{
			write(2, "ERROR\n", 6);
			return (0);
		}
	}
	return (0);
}
