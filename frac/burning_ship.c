/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:03:23 by hfrankly          #+#    #+#             */
/*   Updated: 2019/03/15 19:23:21 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/fractol.h"

void	ft_bs_calc(t_thread *thread)
{
	thread->fractol->nim = fabs(thread->fractol->nre * thread->fractol->nim);
	thread->fractol->nim += thread->fractol->nim;
	thread->fractol->nim += thread->fractol->cim;
	thread->fractol->nre = thread->fractol->nrsqr - thread->fractol->nisqr
	+ thread->fractol->cre;
	thread->fractol->nisqr = thread->fractol->nim * thread->fractol->nim;
	thread->fractol->nrsqr = thread->fractol->nre * thread->fractol->nre;
	thread->fractol->k++;
}

void	ft_init_bs(t_thread *t, int i, int j)
{
	t->fractol->k = 0;
	t->fractol->cre = ((float)i - (float)(SIZEX / 2)) /
	(float)(SIZEX * 0.5 * t->fractol->zoom) + t->fractol->movex;
	t->fractol->cim = ((float)j - (float)(SIZEY / 2)) /
	(float)(SIZEY * 0.5 * t->fractol->zoom) + t->fractol->movey;
	t->fractol->nim = 0;
	t->fractol->nre = 0;
	t->fractol->nisqr = 0;
	t->fractol->nrsqr = 0;
	while ((t->fractol->nisqr + t->fractol->nrsqr <= 4) &&
	(t->fractol->k < t->fractol->iter))
		ft_bs_calc(t);
	if (t->fractol->k == t->fractol->iter)
		*(int*)(t->image->str + (t->fractol->y * SIZEX + t->fractol->x)
		* t->image->bpp) = 0x000000;
	else
		*(int*)(t->image->str + (t->fractol->y * SIZEX + t->fractol->x)
		* t->image->bpp) = ft_colors(t, t->fractol->k);
	t->fractol->y++;
}

void	*ft_bs(void *frctl)
{
	int			y;
	t_fractol	*frac;
	t_thread	*thread;

	thread = (t_thread*)frctl;
	y = thread->fractol->y;
	frac = thread->fractol;
	frac->x = 0;
	while (frac->x < SIZEX)
	{
		frac->y = y;
		while (frac->y < frac->ymax)
			ft_init_bs(frctl, frac->x, frac->y);
		frac->x++;
	}
	return ((void*)(t_thread*)frctl);
}

void	ft_pbs(t_image *image)
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
		(void*)&image->fractol[2], sizeof(t_fractol));
		current_thread[i].fractol->y = s * i;
		current_thread[i].fractol->ymax = s * (i + 1);
		pthread_create(&thread[i], NULL, ft_bs, &current_thread[i]);
	}
	i = -1;
	while (++i < THREAD)
	{
		pthread_join(thread[i], NULL);
		free(current_thread[i].fractol);
	}
}
