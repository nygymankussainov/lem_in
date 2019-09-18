/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putants.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 00:54:20 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/18 14:50:53 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

float		ft_get_line_length(int x0, int y0, int x1, int y1)
{
	return (sqrt(pow((x1 - x0), 2) + pow(y1 - y0, 2)));
}

int			ft_if_draw(int *error, t_point *delta, t_point *sign, t_point *cur)
{
	if ((error[1] = error[0] * 2) > -delta->y)
	{
		error[0] -= delta->y;
		cur->x += sign->x;
	}
	if (error[1] < delta->x)
	{
		error[0] += delta->x;
		cur->y += sign->y;
	}
	if (sqrt(pow((cur->x - cur->x0), 2) + pow(cur->y - cur->y0, 2)) > 1)
	{
		cur->x0 = cur->x;
		cur->y0 = cur->y;
		return (1);
	}
	return (0);
}

void		ft_draw_line(t_sdl *sdl, t_ant *ant, t_point way, int step)
{
	t_point	delta;
	t_point	sign;
	t_point	cur;
	int		*error;

	if (!(error = (int*)malloc(8)))
		exit(0);
	delta.x = fabs(way.x - way.x0);
	delta.y = fabs(way.y - way.y0);
	sign.x = way.x0 < way.x ? 1 : -1;
	sign.y = way.y0 < way.y ? 1 : -1;
	error[0] = delta.x - delta.y;
	cur.x = way.x0;
	cur.y = way.y0;
	cur.x0 = cur.x;
	cur.y0 = cur.y;
	while (step)
		if (ft_if_draw(error, &delta, &sign, &cur))
			step--;
	ant->x = cur.x;
	ant->y = cur.y;
	filledCircleColor(sdl->ren, ant->x, ant->y, ant->radius, 0xFF0058A6);
	SDL_SetRenderDrawColor(sdl->ren, 0x00, 0x00, 0x00, 0x00);
	free(error);
}

void		ft_move_ant(t_sdl *sdl, t_ant *ant, int step)
{
	t_point	way;

	way.x0 = ant->x;
	way.y0 = ant->y;
	way.y = ant->dstroom->y;
	way.x = ant->dstroom->x;
	ft_draw_line(sdl, ant, way, step);
	ant->srcroom->antnbr = 0;
}
