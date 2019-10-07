/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vizualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 23:16:39 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/22 14:57:58 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

void		ft_send_ants1(t_sdl *sdl, int *i, int *step)
{
	static bool pause;

	if (SDL_PollEvent(sdl->e) != 0)
		ft_events(sdl, &pause);
	if (pause == 0 && sdl->ants[*i].x == sdl->ants[*i].dstroom->x
	&& sdl->ants[*i].y == sdl->ants[*i].dstroom->y)
	{
		Mix_ResumeMusic();
		filledCircleColor(sdl->ren, sdl->ants[*i].x,
		sdl->ants[*i].y, sdl->ants[*i].radius, 0xFF0058A6);
		SDL_SetRenderDrawColor(sdl->ren, 0x00, 0x00, 0x00, 0x00);
	}
	else if (pause == 0)
	{
		Mix_ResumeMusic();
		ft_move_ant(sdl, &(sdl->ants[*i]), step[*i]);
	}
	if (pause == 0)
		(*i)++;
}

void		ft_send_ants(t_sdl *sdl, int *length)
{
	int		temp;
	int		*step;
	int		i;

	temp = 0;
	if (!(step = (int*)malloc(sizeof(int) * sdl->arrsize)))
		exit(0);
	i = -1;
	while (++i < sdl->arrsize)
	{
		step[i] = length[i] / sdl->stepsize;
		step[i] = (step[i] == 0) ? 1 : step[i];
	}
	while (temp < sdl->stepsize)
	{
		i = 0;
		SDL_RenderClear(sdl->ren);
		ft_draw_graph(sdl);
		while (i < sdl->arrsize)
			ft_send_ants1(sdl, &i, step);
		temp++;
		SDL_RenderPresent(sdl->ren);
		SDL_Delay(10);
	}
	free(step);
}

int			ft_do_move(t_sdl *sdl)
{
	int		temp;
	int		i;
	int		*length;

	temp = 0;
	sdl->arrsize = ft_array_size(sdl->cmdline);
	if (!(sdl->ants = (t_ant*)malloc(sizeof(t_ant) * sdl->arrsize)))
		exit(0);
	if (!(length = (int*)malloc(sizeof(int) * sdl->arrsize)))
		exit(0);
	ft_get_ants(sdl);
	i = -1;
	while (++i < sdl->arrsize)
		length[i] = ft_get_link_length(sdl->ants[i].srcroom,
		sdl->ants[i].dstroom);
	ft_send_ants(sdl, length);
	i = -1;
	while (++i < sdl->arrsize)
		sdl->ants[i].srcroom->antnbr = -1;
	i = -1;
	while (++i < sdl->arrsize)
		sdl->ants[i].dstroom->antnbr = ft_atoi(&sdl->cmdline[i][1]);
	free(length);
	free(sdl->ants);
	return (0);
}

int			ft_go_ant(t_sdl *sdl)
{
	char	*str;

	while (get_next_line(sdl->fd, &str))
	{
		if (str[0] != 'L')
		{
			free(str);
			continue ;
		}
		sdl->cmdline = ft_strsplit(str, ' ');
		ft_do_move(sdl);
		SDL_Delay(150);
		free(str);
		free_arr(sdl->cmdline);
	}
	return (0);
}

void		vizualizer(t_farm *farm)
{
	t_sdl	*sdl;
	int		quit;

	quit = 0;
	sdl = (t_sdl*)malloc(sizeof(t_sdl));
	if (!(ft_init_sdl(sdl)))
		exit(0);
	sdl->fd = 0;
	sdl->farm = farm;
	sdl->stepsize = 200;
	// ft_play_muzlo(sdl);
	ft_change_coords(sdl);
	SDL_RenderClear(sdl->ren);
	ft_draw_graph(sdl);
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
