/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putants.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 00:54:20 by hfrankly          #+#    #+#             */
/*   Updated: 2019/08/28 14:11:50 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void		ft_linedirtop_a(t_line line, t_sdl *sdl, t_ant *ant, int step)
{
	t_point	delta;
	int		xi;
	int		d;

	xi = 1;
	if (line.xdir < 0)
	{
		xi = -1;
		line.xdir = -line.xdir;
	}
	d = 2 * line.xdir - line.ydir;
	ft_line_init(&line, &delta);
	while (step--)
	{
		if (d > 0)
		{
			line.current.x = line.current.x + xi;
			d = d - 2 * line.ydir;
		}
		d = d + 2 * line.xdir;
		line.current.y++;
	}
	ant->x = line.current.x;
	ant->y = line.current.y;
	ft_draw_circle(sdl, *ant);
}

void		ft_linedirlow_a(t_line line, t_sdl *sdl, t_ant *ant, int step)
{
	t_point	delta;
	float	s;
	int		sdir;

	s = 0;
	line.ydir = (line.ydir > 0) ? 1 : -1;
	line.xdir = (line.xdir > 0) ? 1 : -1;
	sdir = (line.k < 0) ? 1 : -1;
	ft_line_init(&line, &delta);
	while (step--)
	{
		line.current.x += line.xdir;
		s += line.k;
		if (fabs(s) >= 0.5)
		{
			line.current.y += line.ydir;
			s += sdir;
		}
	}
	ant->x = line.current.x;
	ant->y = line.current.y;
	ft_draw_circle(sdl, *ant);
}

void		ft_move_ant(t_sdl *sdl, t_farm *farm, t_ant *ant, int step)
{
	t_line	line;

	line.p0.x = ant->x;
	line.p0.y = ant->y;
	line.p1.x = ant->dstroom->x;
	line.p1.y = ant->dstroom->y;
	line.ydir = line.p1.y - line.p0.y;
	line.xdir = line.p1.x - line.p0.x;
	line.k = (float)(line.ydir) / (float)(line.xdir);
	if (fabs(line.k) >= 1)
	{
		if (line.p0.y > line.p1.y)
		{
			ft_swap_floats(&(line.p0.x), &(line.p1.x));
			ft_swap_floats(&(line.p0.y), &(line.p1.y));
			line.ydir = line.p1.y - line.p0.y;
			line.xdir = line.p1.x - line.p0.x;
		}
		ft_linedirtop_a(line, sdl, ant, step);
	}
	else
		ft_linedirlow_a(line, sdl, ant, step);
	ant->srcroom->antnbr = 0;
}
