/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putants.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 00:54:20 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/10 13:04:51 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

float		ft_get_line_length(int x0, int y0, int x1, int y1)
{
	return (sqrt(pow((x1 - x0), 2) + pow(y1 - y0, 2)));
}

void		ft_draw_line(t_sdl *sdl, t_ant *ant, t_point s, t_point e, int step)
{
	t_point	delta;
	t_point	sign;
	t_point	cur;
	int		error[2];

	delta.x = fabs(e.x - s.x);
	delta.y = fabs(e.y - s.y);
	sign.x = s.x < e.x ? 1 : -1;
	sign.y = s.y < e.y ? 1 : -1;
	error[0] = delta.x - delta.y;
	cur = s;
	cur.x0 = cur.x;
	cur.y0 = cur.y;
	while (step)
	{
		if ((error[1] = error[0] * 2) > -delta.y)
		{
			error[0] -= delta.y;
			cur.x += sign.x;
		}
		if (error[1] < delta.x)
		{
			error[0] += delta.x;
			cur.y += sign.y;
		}
		if (sqrt(pow((cur.x - cur.x0), 2) + pow(cur.y - cur.y0, 2)) > 1)
		{
			cur.x0 = cur.x;
			cur.y0 = cur.y;
			step--;
		}
	}
	ant->x = cur.x;
	ant->y = cur.y;
	filledCircleColor(sdl->ren, ant->x, ant->y, ant->radius, 0xFF0058A6);
	SDL_SetRenderDrawColor(sdl->ren, 0x00, 0x00, 0x00, 0x00);
}

void		ft_move_ant(t_sdl *sdl, t_ant *ant, int step)
{
	t_line	line;

	line.p0.x = ant->x;
	line.p0.y = ant->y;
	line.p1.x = ant->dstroom->x;
	line.p1.y = ant->dstroom->y;
	line.ydir = line.p1.y - line.p0.y;
	line.xdir = line.p1.x - line.p0.x;
	line.k = (float)(line.ydir) / (float)(line.xdir);
	ft_draw_line(sdl, ant, line.p0, line.p1, step);
	ant->srcroom->antnbr = 0;
}