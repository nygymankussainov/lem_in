/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 10:15:06 by hfrankly          #+#    #+#             */
/*   Updated: 2019/03/16 10:27:53 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/fractol.h"

void	ft_init_julia(t_thread *t, int i, int j)
{
	t->fractol->k = 0;
	t->fractol->nre = ((float)i - (float)(SIZEX / 2)) /
	(float)(SIZEX * 0.5 * t->fractol->zoom) + t->fractol->movex;
	t->fractol->nim = ((float)j - (float)(SIZEY / 2)) /
	(float)(SIZEY * 0.5 * t->fractol->zoom) + t->fractol->movey;
	t->fractol->nisqr = t->fractol->nim * t->fractol->nim;
	t->fractol->nrsqr = t->fractol->nre * t->fractol->nre;
	while ((t->fractol->nisqr + t->fractol->nrsqr <= 8) && (t->fractol->k <
	t->fractol->iter))
		ft_frac_calc(t);
	if (t->fractol->k == t->fractol->iter)
		*(int*)(t->image->str + (t->fractol->y * SIZEX + t->fractol->x)
		* t->image->bpp) = 0x000000;
	else
		*(int*)(t->image->str + (t->fractol->y * SIZEX + t->fractol->x) *
		t->image->bpp) = ft_colors(t, t->fractol->k);
	t->fractol->y++;
}

void	*ft_julia(void *frctl)
{
	int			y;
	t_image		*image;
	t_fractol	*frac;
	t_thread	*thread;

	thread = (t_thread*)frctl;
	y = thread->fractol->y;
	image = (t_image*)(thread->image);
	frac = thread->fractol;
	frac->x = 0;
	while (frac->x < SIZEX)
	{
		frac->y = y;
		while (frac->y < frac->ymax)
			ft_init_julia(thread, frac->x, frac->y);
		frac->x++;
	}
	return ((void*)(t_thread*)frctl);
}

void	ft_pjulia(t_image *image)
{
	pthread_t	thread[THREAD];
	t_thread	current_thread[THREAD];
	int			i;
	int			s;

	i = -1;
	s = SIZEY / THREAD;
	while (++i < THREAD)
	{
		current_thread[i].image = image;
		if (!(current_thread[i].fractol =
		(t_fractol*)malloc(sizeof(t_fractol))))
			exit(0);
		ft_memcpy((void*)(current_thread[i].fractol),
		(void*)&image->fractol[1], sizeof(t_fractol));
		current_thread[i].fractol->y = s * i;
		current_thread[i].fractol->ymax = s * (i + 1);
		pthread_create(&thread[i], NULL, ft_julia, &current_thread[i]);
	}
	i = -1;
	while (++i < THREAD)
	{
		pthread_join(thread[i], NULL);
		free(current_thread[i].fractol);
	}
}
