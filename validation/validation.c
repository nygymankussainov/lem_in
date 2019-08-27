/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 11:48:14 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/27 14:54:15 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int		validation(t_room **room, t_farm *farm, t_hashcodes **hashcodes)
{
	t_coords	*coords;

	coords = NULL;
	if (!validate_ants(farm) ||
		!validate_rooms(hashcodes, room, farm, &coords) ||
		!find_and_connect_rooms(farm->line, room, *hashcodes) ||
		!validate_links(room, farm, *hashcodes))
	{
		free_coords(&coords);
		ft_strdel(&farm->line);
		return (0);
	}
	free_coords(&coords);
	return (1);
}
