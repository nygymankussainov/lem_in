/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vizualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 23:16:39 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/02 14:09:21 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void		ft_get_ants(t_sdl *sdl)
{
	int			i;
	t_hash_tab	*ht;
	t_hashcodes	*hc;

	i = -1;
	ht = sdl->farm->h_tab;
	hc = sdl->farm->hashcodes;
	while (++i < sdl->arrsize)
	{
		sdl->ants[i].srcroom = ft_find_ant_room(sdl->farm,
		sdl->cmdline[i][1] - '0'); // изменить для чисел
		sdl->ants[i].dstroom = sdl->cmdline[i][3] - '0';
		sdl->ants[i].x = sdl->ants[i].srcroom->x;
		sdl->ants[i].y = sdl->ants[i].srcroom->y;
		sdl->ants[i].radius = 10;
	}
}

void		ft_send_ants(t_sdl *sdl, int length)
{
	int		temp;
	int		i;

	temp = 0;
	while (++temp < sdl->stepsize)
	{
		i = -1;
		SDL_RenderClear(sdl->ren);
		ft_creategraph(sdl);
		while (++i < sdl->arrsize)
			ft_move_ant(sdl, sdl->farm, &(sdl->ants[i]),
			length / sdl->stepsize);
		SDL_RenderPresent(sdl->ren);
		SDL_Delay(10);
	}
}

int			ft_do_move(t_sdl *sdl)
{
	int		temp;
	int		i;
	int		length;

	temp = 0;
	sdl->arrsize = ft_array_size(sdl->cmdline);
	if (!(sdl->ants = (t_ant*)malloc(sizeof(t_ant) * sdl->arrsize)))
		exit(0);
	ft_get_ants(sdl);
	length = ft_get_link_length(sdl, sdl->ants[0].srcroom, sdl->ants[0].dstroom);
	ft_send_ants(sdl, length);
	i = -1;
	while (++i < sdl->arrsize)
	{
		sdl->ants[i].dstroom = hash_func(sdl->cmdline[i][1]);
		if (sdl->ants[i].antnbr == sdl->ants[i].srcroom->antnbr)
			sdl->ants[i].srcroom->antnbr = -1;
	}
	return (0);
}

int			ft_go_ant(t_sdl *sdl)
{
	char	*str;

	while (get_next_line(sdl->fd, &str))
	{
		if (str[0] != 'L')
			continue ;
		sdl->cmdline = ft_strsplit(str, ' ');
		ft_do_move(sdl);
		SDL_Delay(100);
		free(str);
		free_arr(sdl->cmdline);
	}
	return (0);
}

void		ft_change_coords(t_sdl *sdl)
{
	t_hash_tab	*ht;
	t_hashcodes	*hc;
	t_room		*room;

	sdl->map = ft_initmap(sdl->farm, ft_find_maxcoords(sdl->farm));
	ht = sdl->farm->h_tab;
	while (hc)
	{
		ht[hc->hash_code].room->x = SIZEY / 2 - (SIZEY / sdl->map.maxdif)
		* (sdl->map.xcenter - ht[hc->hash_code].room->x);
		ht[hc->hash_code].room->y = SIZEY / 2 - (SIZEY / sdl->map.maxdif)
		* (sdl->map.ycenter - ht[hc->hash_code].room->y);
		if (ht[hc->hash_code].room->next)
		{
			room = ht[hc->hash_code].room->next;
			while (room)
			{
				room->x = SIZEX / 2 - (SIZEX / sdl->map.maxdif)
				* (sdl->map.xcenter - room->x);
				room->y = SIZEY / 2 - (SIZEY / sdl->map.maxdif)
				* (sdl->map.ycenter - room->y);
				room = room->next;
			}
		}
		hc = hc->next;
	}
}

void		vizualizer(t_farm *farm)
{
	t_sdl	*sdl;
	int		quit;

	quit = 0;
	sdl = (t_sdl*)malloc(sizeof(t_sdl));
	if (!(ft_init_sdl(sdl)))
		return (0);
	sdl->fd = 0;
	sdl->farm = farm;
	sdl->stepsize = 100;
	ft_change_coords(sdl);
	ft_creategraph(sdl);
	SDL_RenderPresent(sdl->ren);
	// ft_go_ant(sdl);
	while (!quit)
	{
		while (SDL_PollEvent(sdl->e) != 0)
			if (sdl->e->type == SDL_QUIT ||
		(sdl->e->type == SDL_KEYDOWN && sdl->e->key.keysym.sym == SDLK_ESCAPE))
				quit = 1;
	}
	ft_close_sdl(sdl);
}
