/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 16:38:26 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/11 14:36:25 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_sign(int bigl, char *binary)
{
	if (bigl)
		ft_putchar(binary[48]);
	else
		ft_putchar(binary[0]);
}

int		parse_b(t_flags *fl, t_float value)
{
	int		ret;

	if (fl->m == 1)
		ft_putstr(value.exp);
	else if (fl->m == 2)
		ft_putstr(value.mant);
	else if (fl->z)
		print_sign(fl->bigl, value.binary);
	else
	{
		print_sign(fl->bigl, value.binary);
		ft_putchar('.');
		ft_putstr(value.exp);
		ft_putchar('.');
		ft_putstr(value.mant);
	}
	ret = ft_strlen(value.binary) + 2;
	ret -= fl->bigl ? 48 : 0;
	ret = fl->m == 1 ? ft_strlen(value.exp) : ret;
	ret = fl->m == 2 && !fl->bigl ? ft_strlen(value.mant) : ret;
	ret = fl->m == 2 && fl->bigl ? ft_strlen(value.mant) + 1 : ret;
	ret = fl->z ? 1 : ret;
	return (ret);
}
