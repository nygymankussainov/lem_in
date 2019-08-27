/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vizualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 23:16:39 by hfrankly          #+#    #+#             */
/*   Updated: 2019/08/25 23:27:41 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_get_ants(t_sdl *sdl)
{
	int		i;
	int		*maxcoords;
	t_map	map;

	maxcoords = ft_find_maxcoords(*(sdl->farm));
	map = ft_initmap(*(sdl->farm), maxcoords);
	i = -1;
	while (++i < sdl->arrsize)
	{
		sdl->ants[i].srcroom = ft_find_ant_room(sdl->farm,
		sdl->cmdline[i][1] - '0'); // изменить для чисел
		sdl->ants[i].dstroom = sdl->cmdline[i][3] - '0';
		sdl->ants[i].x = SIZEY / 2 - (SIZEY / map.maxdif)
		* (map.xcenter - sdl->farm->room[sdl->ants[i].srcroom].x);
		sdl->ants[i].y = SIZEY / 2 - (SIZEY / map.maxdif)
		* (map.ycenter - sdl->farm->room[sdl->ants[i].srcroom].y);
		sdl->ants[i].radius = 10;
	}
	sdl->map = map;
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
		ft_creategraph(*sdl->farm, sdl);
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
	length = ft_get_link_length(sdl, sdl->farm->room[sdl->ants[0].srcroom],
	sdl->farm->room[sdl->ants[0].dstroom]);
	ft_send_ants(sdl, length);
	i = -1;
	while (++i < sdl->arrsize)
	{
		sdl->farm->room[sdl->ants[i].dstroom].antnbr = sdl->cmdline[i][1] - '0';
		if (sdl->ants[i].antnbr == sdl->farm->room[sdl->ants[i].srcroom].antnbr)
			sdl->farm->room[sdl->ants[i].srcroom].antnbr = -1;
	}
	return (0);
}

int			ft_go_ant(t_sdl *sdl)
{
	char	*str;

	while (get_next_line(sdl->fd, &str))
	{
		sdl->cmdline = ft_strsplit(str, ' ');
		ft_do_move(sdl);
		SDL_Delay(100);
		free(str);
		free_arr(sdl->cmdline);
	}
	return (0);
}

void		ft_vizualizer(t_sdl *sdl, t_farm *farm)
{
	sdl->fd = open("test", O_RDONLY);
	sdl->farm = farm;
	sdl->stepsize = 150;
	ft_creategraph(*(sdl->farm), sdl);
	SDL_RenderPresent(sdl->ren);
	ft_go_ant(sdl);
}
