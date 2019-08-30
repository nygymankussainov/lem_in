/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 18:33:57 by hfrankly          #+#    #+#             */
/*   Updated: 2019/08/30 11:47:55 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

void		ft_swap_floats(float *a, float *b)
{
	float c;

	c = *a;
	*a = *b;
	*b = c;
}

void		ft_line_init(t_line *line, t_point *delta)
{
	line->current.y = line->p0.y;
	line->current.x = line->p0.x;
	line->current.color = line->p0.color;
	delta->x = line->p1.x - line->current.x;
	delta->y = line->p1.y - line->current.y;
}

void		ft_linedirtop(t_line line, t_sdl *sdl)
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
	while (line.current.y != line.p1.y)
	{
		SDL_RenderDrawPoint(sdl->ren, line.current.x, line.current.y);
		if (d > 0)
		{
			line.current.x = line.current.x + xi;
			d = d - 2 * line.ydir;
		}
		d = d + 2 * line.xdir;
		line.current.y++;
	}
}

void		ft_linedirlow(t_line line, t_sdl *sdl)
{
	t_sdl	*par;
	t_point	delta;
	float	s;
	int		sdir;

	par = (t_sdl*)sdl;
	s = 0;
	line.ydir = (line.ydir > 0) ? 1 : -1;
	line.xdir = (line.xdir > 0) ? 1 : -1;
	sdir = (line.k < 0) ? 1 : -1;
	ft_line_init(&line, &delta);
	while (line.current.x - line.p0.x != line.p1.x - line.p0.x)
	{
		line.current.x += line.xdir;
		SDL_RenderDrawPoint(sdl->ren, line.current.x, line.current.y);
		s += line.k;
		if (fabs(s) >= 0.5)
		{
			line.current.y += line.ydir;
			s += sdir;
		}
	}
}

void		ft_bresenham(t_sdl *sdl, int *coord)
{
	t_line	line;

	line.p0.x = coord[0];
	line.p0.y = coord[1];
	line.p1.x = coord[2];
	line.p1.y = coord[3];
	line.ydir = line.p1.y - line.p0.y;
	line.xdir = line.p1.x - line.p0.x;
	line.k = (float)(line.ydir) / (float)(line.xdir);
	SDL_SetRenderDrawColor(sdl->ren, 0xAA, 0xAA, 0xAA, 0x00);
	if (fabs(line.k) >= 1)
	{
		if (line.p0.y > line.p1.y)
		{
			ft_swap_floats(&(line.p0.x), &(line.p1.x));
			ft_swap_floats(&(line.p0.y), &(line.p1.y));
			line.ydir = line.p1.y - line.p0.y;
			line.xdir = line.p1.x - line.p0.x;
		}
		ft_linedirtop(line, sdl);
	}
	else
		ft_linedirlow(line, sdl);
	SDL_SetRenderDrawColor(sdl->ren, 0x00, 0x00, 0x00, 0x00);
}
