/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:45:43 by hfrankly          #+#    #+#             */
/*   Updated: 2019/08/25 23:17:50 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		free_arr(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int			ft_array_size(char **arr)
{
	int size;

	size = 0;
	while (arr[size])
		size++;
	return (size);
}

int		main(void)
{
	t_farm	farm;
	t_room	*room;
	t_sdl	*sdl;
	int		quit;

	quit = 0;
	sdl = (t_sdl*)malloc(sizeof(t_sdl));
	if (!(ft_init_sdl(sdl)))
		return (0);
	farm.room = (t_room*)malloc(sizeof(t_room) * 6);
	room = farm.room;
	room[0].x = 2;
	room[0].y = 0;
	room[1].x = 0;
	room[1].y = 2;
	room[2].x = 4;
	room[2].y = 2;
	room[3].x = 4;
	room[3].y = 4;
	room[4].x = 2;
	room[4].y = 6;
	room[5].x = 0;
	room[5].y = 4;
	room[0].link = (t_link*)malloc(sizeof(t_link));
	room[0].link->next = (t_link*)malloc(sizeof(t_link));
	room[1].link = (t_link*)malloc(sizeof(t_link));
	room[2].link = (t_link*)malloc(sizeof(t_link));
	room[3].link = (t_link*)malloc(sizeof(t_link));
	room[4].link = (t_link*)malloc(sizeof(t_link));
	room[5].link = (t_link*)malloc(sizeof(t_link));
	room[0].link->next->next = NULL;
	room[1].link->next = NULL;
	room[2].link->next = NULL;
	room[3].link->next = NULL;
	room[4].link->next = NULL;
	room[5].link->next = NULL;
	room[0].link->iroom = 1;
	room[0].link->next->iroom = 2;
	room[1].link->iroom = 5;
	room[2].link->iroom = 3;
	room[3].link->iroom = 4;
	room[5].link->iroom = 4;
	farm.room_count = 6;
	farm.link_count = 6;
	farm.ants = 5;
	farm.start = 0;
	farm.end = 4;
	while (!quit)
	{
		if (!quit)
		{
			ft_vizualizer(sdl, &farm);
			quit = 1;
		}
		while (SDL_PollEvent(sdl->e) != 0)
			if (sdl->e->type == SDL_QUIT ||
		(sdl->e->type == SDL_KEYDOWN && sdl->e->key.keysym.sym == SDLK_ESCAPE))
				quit = 1;
	}
	ft_close_sdl(sdl);
	return (0);
}
