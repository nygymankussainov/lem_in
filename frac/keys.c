/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:34:14 by hfrankly          #+#    #+#             */
/*   Updated: 2019/03/16 11:23:04 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/fractol.h"

void	ft_key0(t_mlx *mlx, int keycode)
{
	if (keycode == 18)
	{
		mlx->image.i = 0;
		ft_init_fractol(mlx);
		ft_pmbrt(&mlx->image);
	}
	else if (keycode == 19)
	{
		mlx->image.i = 1;
		ft_init_fractol(mlx);
		ft_pjulia(&mlx->image);
	}
	else if (keycode == 20)
	{
		mlx->image.i = 2;
		ft_init_fractol(mlx);
		ft_pbs(&mlx->image);
	}
	else if (keycode == 21)
	{
		mlx->image.i = 3;
		ft_init_fractol(mlx);
		ft_pspider(&mlx->image);
	}
}

void	ft_key1(t_mlx *mlx, int keycode)
{
	if (keycode == 78)
		mlx->image.fractol[mlx->image.i].iter -= 10;
	else if (keycode == 69)
		mlx->image.fractol[mlx->image.i].iter += 10;
	else if (keycode == 126)
		mlx->image.fractol[mlx->image.i].movey += 0.1 /
		mlx->image.fractol[mlx->image.i].zoom;
	else if (keycode == 125)
		mlx->image.fractol[mlx->image.i].movey -= 0.1 /
		mlx->image.fractol[mlx->image.i].zoom;
	else if (keycode == 123)
		mlx->image.fractol[mlx->image.i].movex += 0.1 /
		mlx->image.fractol[mlx->image.i].zoom;
	else if (keycode == 124)
		mlx->image.fractol[mlx->image.i].movex -= 0.1 /
		mlx->image.fractol[mlx->image.i].zoom;
	else if (keycode == 83)
		mlx->image.n = 0;
	else if (keycode == 84)
		mlx->image.n = 1;
	else if (keycode == 85)
		mlx->image.n = 2;
	else if (keycode == 86)
		mlx->image.n = 3;
}

int		ft_key(int k, void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx*)param;
	if (k == 53)
		exit(0);
	if (k == 87)
		mlx->image.n = 4;
	if (k == 18 || k == 19 || k == 20 || k == 21)
		ft_key0(mlx, k);
	else if (k == 21 || k == 78 || k == 69 || k == 126 ||
	k == 125 || k == 123 || k == 124 || k == 83 || k == 84 ||
	k == 85 || k == 86)
		ft_key1(mlx, k);
	if (mlx->image.i == 3)
		ft_pspider(&mlx->image);
	else if (mlx->image.i == 2)
		ft_pbs(&mlx->image);
	else if (mlx->image.i == 1)
		ft_pjulia(&mlx->image);
	else if (mlx->image.i == 0)
		ft_pmbrt(&mlx->image);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
	mlx->image.image_ptr, 0, 0);
	return (0);
}
