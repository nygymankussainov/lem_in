/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 15:28:58 by hfrankly          #+#    #+#             */
/*   Updated: 2019/08/30 13:42:28 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

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

void	ft_draw_vertex(t_sdl *sdl, const t_room *room, int room_count)
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
			x = abs(j - room->x);
			y = abs(i - room->y);
			if ((x - room->x) * (x - room->x)
			+ (y - room->y) * (y - room->y) <= r * r)
				SDL_RenderDrawPoint(sdl->ren, x, y);
		}
	}
	SDL_SetRenderDrawColor(sdl->ren, 0x00, 0x00, 0x00, 0x00);
}

void	ft_draw_link(t_sdl *sdl, const t_room *room)
{
	int		*coords;
	t_link	*hroom;

	if (!(coords = (int *)malloc(4 * 4)))
		exit(0);
	coords[0] = room->x;
	coords[1] = room->y;
	if (room->link)
		hroom = room->link;
	else
		return ;
	while (hroom)
	{
		coords[2] = hroom->room->x;
		coords[3] = hroom->room->y;
		hroom = hroom->next;
		ft_bresenham(sdl, coords);
	}
	free(coords);
}

void	ft_creategraph(t_sdl *sdl)
{
	t_room		*room;
	t_hash_tab	*ht;
	t_hashcodes	*hc;

	hc = sdl->farm->hashcodes;
	ht = sdl->farm->h_tab;
	while (hc)
	{
		room = ht[hc->hash_code].room;
		while (room)
		{
			if (room->status == 's')
				SDL_SetRenderDrawColor(sdl->ren, 0x67, 0x9B, 0x00, 0x00);
			else if (room->status == 'e')
				SDL_SetRenderDrawColor(sdl->ren, 0xB7, 0x2E, 0x3E, 0x00);
			else
				SDL_SetRenderDrawColor(sdl->ren, 0xFF, 0xFF, 0xFF, 0x00);
			ft_draw_vertex(sdl, ht[hc->hash_code].room, sdl->farm->room_count);
			room = room->next;
		}
		hc = hc->next;
	}
	hc = sdl->farm->hashcodes;
	while (hc)
	{
		room = ht[hc->hash_code].room;
		while (room)
		{
			if (hc->hash_code != sdl->farm->end)
					ft_draw_link(sdl, ht[hc->hash_code].room);
			room = room->next;
		}
		hc = hc->next;
	}
}
