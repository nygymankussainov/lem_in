/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 15:28:58 by hfrankly          #+#    #+#             */
/*   Updated: 2019/08/25 14:12:31 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_draw_circle(t_sdl *sdl, t_ant ant)
{
	int		i;
	int		j;
	int		x;
	int		y;

	i = -ant.radius - 1;
	SDL_SetRenderDrawColor(sdl->ren, 0xA5, 0xFF, 0x2A, 0xFF);
	while (++i < ant.radius)
	{
		j = -ant.radius - 1;
		while (++j < ant.radius)
		{
			x = abs(j - ant.x);
			y = abs(i - ant.y);
			if ((x - ant.x) * (x - ant.x)
			+ (y - ant.y) * (y - ant.y) <= ant.radius * ant.radius)
				SDL_RenderDrawPoint(sdl->ren, x, y);
		}
	}
	SDL_SetRenderDrawColor(sdl->ren, 0x00, 0x00, 0x00, 0x00);
}

void	ft_draw_vertex(t_sdl *sdl, t_room room, int room_count)
{
	int		i;
	int		j;
	int		r;
	int		x;
	int		y;

	r = (room_count > 20) ? SIZEX / room_count : 25;
	i = -r - 1;
	while (++i < r)
	{
		j = -r - 1;
		while (++j < r)
		{
			x = abs(j - room.x);
			y = abs(i - room.y);
			if ((x - room.x) * (x - room.x)
			+ (y - room.y) * (y - room.y) <= r * r)
				SDL_RenderDrawPoint(sdl->ren, x, y);
		}
	}
	SDL_SetRenderDrawColor(sdl->ren, 0x00, 0x00, 0x00, 0x00);
}

void	ft_draw_link(t_sdl *sdl, t_farm farm, t_room room)
{
	int		*coords;

	if (!(coords = (int *)malloc(4 * 4)))
		exit(0);
	coords[0] = room.x;
	coords[1] = room.y;
	while (room.link)
	{
		coords[2] = farm.room[room.link->iroom].x;
		coords[3] = farm.room[room.link->iroom].y;
		room.link = room.link->next;
		ft_bresenham(sdl, coords);
	}
	free(coords);
}

void	ft_creategraph(t_farm farm, t_sdl *sdl)
{
	t_map	map;
	int		i;

	i = -1;
	map = ft_initmap(farm, ft_find_maxcoords(farm));
	while (++i < farm.room_count)
	{
		farm.room[i].x = SIZEY / 2
		- (SIZEY / map.maxdif) * (map.xcenter - farm.room[i].x);
		farm.room[i].y = SIZEY / 2
		- (SIZEY / map.maxdif) * (map.ycenter - farm.room[i].y);
		if (i == farm.start)
			SDL_SetRenderDrawColor(sdl->ren, 0x67, 0x9B, 0x00, 0x00);
		else if (i == farm.end)
			SDL_SetRenderDrawColor(sdl->ren, 0xB7, 0x2E, 0x3E, 0x00);
		else
			SDL_SetRenderDrawColor(sdl->ren, 0xFF, 0xFF, 0xFF, 0x00);
		ft_draw_vertex(sdl, farm.room[i], farm.room_count);
	}
	i = -1;
	while (++i < farm.room_count)
		if (i != farm.end)
			ft_draw_link(sdl, farm, farm.room[i]);
}
