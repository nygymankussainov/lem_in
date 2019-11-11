/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:12:15 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/11 14:35:58 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_binary_bigl(long double db, char **str, char **exp, char **mant)
{
	__int128_t	nb;
	int			j;
	int			i;

	j = 127;
	if (!(*str = (char *)ft_memalloc(sizeof(char) + 129)))
		exit(12);
	(*str)[128] = '\0';
	i = 0;
	ft_memcpy(&nb, &db, 16);
	while (j >= 0)
	{
		(*str)[i] = ((nb & ((__int128_t)1 << j)) >> j) + '0';
		j--;
		i++;
	}
	*exp = ft_strncpy(*exp, *str + 49, 15);
	(*exp)[15] = '\0';
	*mant = ft_strncpy(*mant, *str + 64, 63);
	(*mant)[63] = '\0';
	return (ft_atoi_base(*exp, 2) - 16383);
}

int		get_binary(double db, char **str, char **exp, char **mant)
{
	__int64_t	nb;
	int			j;
	int			i;

	j = 63;
	if (!(*str = (char *)ft_memalloc(sizeof(char) + 65)))
		exit(12);
	(*str)[64] = '\0';
	i = 0;
	ft_memcpy(&nb, &db, 8);
	while (j >= 0)
	{
		(*str)[i] = ((nb & ((__int64_t)1 << j)) >> j) + '0';
		j--;
		i++;
	}
	(*str)[0] = (*str)[0] != '0' ? '1' : (*str)[0];
	*exp = ft_strncpy(*exp, *str + 1, 11);
	(*exp)[11] = '\0';
	*mant = ft_strncpy(*mant, *str + 12, 52);
	(*mant)[52] = '\0';
	return (ft_atoi_base(*exp, 2) - 1023);
}

int		is_nan_inf(const char **format, long double db)
{
	if (db != db)
	{
		if (**FRMT == 'F')
			write(1, "NAN", 3);
		else
			write(1, "nan", 3);
		(*FRMT)++;
	}
	else if (db == (1.0 / 0.0) || db == -(1.0 / 0.0))
	{
		if (db == -(1.0 / 0.0))
			write(1, "-", 1);
		if (**FRMT == 'F')
			write(1, "INF", 3);
		else
			write(1, "inf", 3);
		(*FRMT)++;
		if (db == -(1.0 / 0.0))
			return (4);
	}
	return (3);
}

void	create_strcut(char **exp, char **mant, int bigl)
{
	if (bigl)
	{
		if (!(*exp = (char *)ft_memalloc(sizeof(char) * 16)) ||
			!(*mant = (char *)ft_memalloc(sizeof(char) * 64)))
			exit(12);
	}
	else
	{
		if (!(*exp = (char *)ft_memalloc(sizeof(char) * 12)) ||
			!(*mant = (char *)ft_memalloc(sizeof(char) * 53)))
			exit(12);
	}
}

int		parse_f(const char **format, va_list valist, t_flags *fl)
{
	int			ret;
	t_float		value;

	value.sign = 0;
	value.db = fl->bigl ? va_arg(valist, long double) :
		(double)va_arg(valist, double);
	if (fl->conv != 'b' &&
		(value.db != value.db || value.db == (1.0 / 0.0) || value.db == -(1.0 / 0.0)))
		return (is_nan_inf(FRMT, value.db));
	create_strcut(&value.exp, &value.mant, fl->bigl);
	if (fl->bigl)
		value.exp_i = get_binary_bigl(value.db, &value.binary, &value.exp, &value.mant);
	else
		value.exp_i = get_binary(value.db, &value.binary, &value.exp, &value.mant);
	value.sign = fl->bigl && value.binary[48] == '1' ? -1 : value.sign;
	value.sign = !fl->bigl && value.binary[0] == '1' ? -1 : value.sign;
	value.isint = value.exp_i >= 0 ? 1 : 0;
	ret = fl->conv != 'b' ? integer_part(value, fl) : parse_b(fl, value);
	(*FRMT)++;
	ft_strdel(&value.binary);
	ft_strdel(&value.exp);
	ft_strdel(&value.mant);
	return (ret);
}
