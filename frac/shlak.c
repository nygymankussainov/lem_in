/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlak.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:25:10 by hfrankly          #+#    #+#             */
/*   Updated: 2019/03/16 09:36:17 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/fractol.h"

int		ft_close(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

void	ft_frac_spot(char *name, t_mlx *mlx)
{
	if (!ft_strcmp(name, "mandelbrot"))
	{
		mlx->image.i = 0;
		ft_init_fractol(mlx);
		ft_pmbrt(&mlx->image);
	}
	else if (!ft_strcmp(name, "julia"))
	{
		mlx->image.i = 1;
		ft_init_fractol(mlx);
		ft_pjulia(&mlx->image);
	}
	else if (!ft_strcmp(name, "bs"))
	{
		mlx->image.i = 2;
		ft_init_fractol(mlx);
		ft_pbs(&mlx->image);
	}
	else if (!ft_strcmp(name, "spider"))
	{
		mlx->image.i = 3;
		ft_init_fractol(mlx);
		ft_pspider(&mlx->image);
	}
}
