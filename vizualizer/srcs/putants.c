/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putants.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 00:54:20 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/02 16:45:37 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

int		ft_get_line_length(int x0, int y0, int x1, int y1)
{
	return (sqrt(pow((x1 - x0), 2) + pow(y1 - y0, 2)));
}

void		ft_linedirtop_a(t_line line, t_sdl *sdl, t_ant *ant, int step)
{
	t_point	delta;
	t_point	start;
	int		xi;
	int		d;

	xi = 1;
	if (line.xdir < 0)
	{
		xi = -1;
		line.xdir = -line.xdir;
	}
	start.x = ant->x;
	start.y = ant->y;
	d = 2 * line.xdir - line.ydir;
	ft_line_init(&line, &delta);
	while (1)
	{
		if (d > 0)
		{
			line.current.x = line.current.x + xi;
			d = d - 2 * line.ydir;
		}
		d = d + 2 * line.xdir;
		line.current.y++;
		if (ft_get_line_length(start.x, start.y, line.current.x, line.current.y) > step)
			break;
	}
	ant->x = line.current.x;
	ant->y = line.current.y;
	SDL_SetRenderDrawColor(sdl->ren, 0xA5, 0xFF, 0x2A, 0xFF);
	ft_draw_circle(sdl->ren, ant->x, ant->y, ant->radius);
}

void		ft_linedirlow_a(t_line line, t_sdl *sdl, t_ant *ant, int step)
{
	t_point	delta;
	t_point	start;
	float	s;
	int		sdir;

	s = 0;
	line.ydir = (line.ydir > 0) ? 1 : -1;
	line.xdir = (line.xdir > 0) ? 1 : -1;
	sdir = (line.k < 0) ? 1 : -1;
	start.x = ant->x;
	start.y = ant->y;
	ft_line_init(&line, &delta);
	while (1)
	{
		line.current.x += line.xdir;
		s += line.k;
		if (fabs(s) >= 0.5)
		{
			line.current.y += line.ydir;
			s += sdir;
		}
		if (ft_get_line_length(start.x, start.y, line.current.x, line.current.y) > step)
			break;
	}
	ant->x = line.current.x;
	ant->y = line.current.y;
	SDL_SetRenderDrawColor(sdl->ren, 0xA5, 0xFF, 0x2A, 0xFF);
	ft_draw_circle(sdl->ren, ant->x, ant->y, ant->radius);
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
