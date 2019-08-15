/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 10:17:10 by hfrankly          #+#    #+#             */
/*   Updated: 2019/03/16 09:52:54 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/fractol.h"

void	ft_zoom(t_mlx *mlx, int i, int x, int y)
{
	if (i == -1)
	{
		mlx->image.fractol[mlx->image.i].zoom /= pow(1.05, 2);
		mlx->image.fractol[mlx->image.i].movey -= ((y - HALF_W) / 3500.0 /
		mlx->image.fractol[mlx->image.i].zoom) / 1.5;
		mlx->image.fractol[mlx->image.i].movex -= ((x - HALF_W) / 3500.0 /
		mlx->image.fractol[mlx->image.i].zoom) / 1.5;
	}
	else if (i == 1)
	{
		mlx->image.fractol[mlx->image.i].zoom *= pow(1.05, 2);
		mlx->image.fractol[mlx->image.i].movey += ((y - HALF_W) / 3500.0 /
		mlx->image.fractol[mlx->image.i].zoom) / 1.5;
		mlx->image.fractol[mlx->image.i].movex += ((x - HALF_W) / 3500.0 /
		mlx->image.fractol[mlx->image.i].zoom) / 1.5;
	}
}

int		ft_mouse_press(int button, int x, int y, void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx*)param;
	if (button == 1 && mlx->image.i == 1)
		mlx->image.fractol[1].julia_move =
		mlx->image.fractol[1].julia_move == 1 ? 0 : 1;
	if (button == 4)
		ft_zoom(mlx, -1, x, y);
	if (button == 5)
		ft_zoom(mlx, 1, x, y);
	if (mlx->image.i == 3)
		ft_pspider(&mlx->image);
	if (mlx->image.i == 2)
		ft_pbs(&mlx->image);
	if (mlx->image.i == 1)
		ft_pjulia(&mlx->image);
	if (mlx->image.i == 0)
		ft_pmbrt(&mlx->image);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
	mlx->image.image_ptr, 0, 0);
	return (0);
}

int		ft_mouse_move(int x, int y, void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx*)param;
	if (mlx->image.fractol[mlx->image.i].julia_move == 1
	&& x <= SIZEX && y <= SIZEY && x >= 0 && y >= 0)
	{
		mlx->image.fractol[mlx->image.i].cre = ((float)x - (float)(SIZEX / 2)) /
		(float)(SIZEX * 0.5 * mlx->image.fractol[mlx->image.i].zoom) +
		mlx->image.fractol[mlx->image.i].movex;
		mlx->image.fractol[mlx->image.i].cim = ((float)y - (float)(SIZEY / 2)) /
		(float)(SIZEY * 0.5 * mlx->image.fractol[mlx->image.i].zoom) +
		mlx->image.fractol[mlx->image.i].movey;
		ft_pjulia(&mlx->image);
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
		mlx->image.image_ptr, 0, 0);
	}
	return (0);
}
