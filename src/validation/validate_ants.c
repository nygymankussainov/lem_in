/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_ants.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 12:43:45 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/14 11:45:19 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lem_in.h"

int		validate_ants(t_farm *farm)
{
	while (farm->ants == 0 && get_next_line(farm->fd, &farm->line) == 1)
	{
		if (farm->line && isint(farm->line, 'a'))
		{
			if (!(farm->ants = ft_atoi(farm->line)))
				return (0);
		}
		else if (farm->line && farm->line[0] == '#'
			&& ft_strcmp("##start", farm->line)
			&& ft_strcmp("##end", farm->line))
		{
			ft_strdel(&farm->line);
			continue ;
		}
		else
			return (0);
		ft_strdel(&farm->line);
	}
	return (1);
}
