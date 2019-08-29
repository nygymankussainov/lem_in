/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 23:15:44 by hfrankly          #+#    #+#             */
/*   Updated: 2019/08/27 17:06:18 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

int		ft_init_sdl(t_sdl *sdl)
{
	sdl->win = NULL;
	sdl->sfc = NULL;
	sdl->e = NULL;
	if (!(sdl->e = (SDL_Event*)malloc(sizeof(SDL_Event))))
		return (0);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		return (0);
	else
	{
		SDL_CreateWindowAndRenderer(SIZEX, SIZEY, 0, &sdl->win, &sdl->ren);
		if (sdl->win == NULL || sdl->ren == NULL)
			return (0);
	}
	return (1);
}

void	ft_close_sdl(t_sdl *sdl)
{
	free(sdl->e);
	SDL_DestroyWindow(sdl->win);
	SDL_DestroyRenderer(sdl->ren);
	SDL_Quit();
	free(sdl);
}
