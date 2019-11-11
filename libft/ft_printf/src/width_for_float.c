/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_for_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 15:46:28 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/11 14:32:30 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_zero_or_space(int width, int zero, int ret)
{
	if (width > 0)
	{
		ret += width;
		while (width--)
		{
			if (!zero)
				ft_putchar(' ');
			else
				ft_putchar('0');
		}
	}
	return (ret);
}

int		width_for_float(char *str, t_flags *fl, int ret)
{
	if (fl->pos && fl->zero)
		write(1, "+", 1);
	else if (fl->neg)
	{
		if (fl->pos)
			write(1, "+", 1);
		ft_putstr(str);
	}
	fl->width -= ret;
	ret = print_zero_or_space(fl->width, fl->zero, ret);
	if ((fl->pos && !fl->neg) || (!fl->pos && !fl->neg))
	{
		if (fl->pos && !fl->neg && !fl->zero)
			write(1, "+", 1);
		ft_putstr(str);
	}
	return (ret);
}
