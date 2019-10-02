/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_ants.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 12:43:45 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/02 14:54:40 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int		validate_ants(t_farm *farm)
{
	while (farm->ants == 0 && get_next_line(farm->newfd, &farm->line) == 1)
	{
		if (isint(farm->line, 'a'))
			farm->ants = ft_atoi(farm->line);
		else if (farm->line[0] == '#' && ft_strcmp("##start", farm->line)
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
