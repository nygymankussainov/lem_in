/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 15:28:58 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/12 22:12:22 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

void	ft_draw_circle(SDL_Renderer *ren, int xc, int yc, int r)
{
	int		i;
	int		j;
	int		till;

	i = -r;
	while (i <= 0)
	{
		till = sqrt((r * r - i * i));
		j = -till;
		while (j <= till)
		{
			SDL_RenderDrawPoint(ren, xc - j, yc - i);
			SDL_RenderDrawPoint(ren, xc - j, yc + i);
			j++;
		}
		i++;
	}
	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
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
		SDL_SetRenderDrawColor(sdl->ren, 0xAA, 0xAA, 0xAA, 0xFF);
		SDL_RenderDrawLine(sdl->ren, coords[0],
		coords[1], coords[2], coords[3]);
	}
	free(coords);
}

void	ft_draw_rooms(t_sdl *sdl)
{
	t_room		*room;
	t_hash_tab	*ht;
	t_hashcodes	*hc;
	int			color;

	hc = sdl->farm->hashcodes;
	ht = sdl->farm->h_tab;
	while (hc)
	{
		room = ht[hc->hash_code].room;
		while (room)
		{
			if (room->status == 's')
				color = 0xFF3E2EB7;
			else if (room->status == 'e')
				color = 0xFF80255E;
			else
				color = 0xFFFFFFFF;
			filledCircleColor(sdl->ren, room->x, room->y,
			(sdl->farm->room_count > 10) ? (SIZEX / 2)
			/ sdl->farm->room_count - 5 : 20, color);
			room = room->next;
		}
		hc = hc->next;
	}
}

void	ft_draw_graph(t_sdl *sdl)
{
	t_room		*room;
	t_hash_tab	*ht;
	t_hashcodes	*hc;

	ft_draw_rooms(sdl);
	hc = sdl->farm->hashcodes;
	ht = sdl->farm->h_tab;
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
