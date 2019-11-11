/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:43:45 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/11 14:18:07 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	get_nbr_d(const char **format, va_list valist, t_flags *fl)
{
	long long	nbr;

	fl->conv = **FRMT;
	if (fl->l == 2 || fl->conv == 'D')
		nbr = (long long)va_arg(valist, long long);
	else if (fl->l == 1)
		nbr = (long)va_arg(valist, long);
	else if (fl->h == 2)
		nbr = (char)va_arg(valist, int);
	else if (fl->h == 1)
		nbr = (short)va_arg(valist, int);
	else
		nbr = (long long)va_arg(valist, int);
	return (nbr);
}

int			ifwhitesp(t_flags *fl, int *tmp, int key, int ret)
{
	if (fl->whitesp && fl->zero_padd && fl->width > ret
		&& fl->zero_padd > ret && fl->zero_padd > fl->width)
	{
		(*tmp)++;
		ft_putchar(' ');
	}
	if (fl->whitesp && (fl->width <= ret || fl->neg ||
		(key && !fl->zero_padd) || (fl->width && fl->zero))
		&& fl->sign > 0 && !fl->pos)
	{
		write(1, " ", 1);
		if (fl->neg && fl->width > ret)
		{
			fl->width -= fl->zero_padd ? 1 : 0;
			ret += !fl->zero_padd ? 1 : 0;
			(*tmp) += fl->zero_padd ? 1 : 0;
		}
		else if (fl->width && fl->zero && !key)
			ret += fl->width > ret ? 1 : 0;
		else if (key)
			(*tmp) += fl->width > ret ? 1 : 0;
	}
	return (ret);
}

int			manage_width(char *str, t_flags *fl)
{
	int		ret;
	int		tmp;
	int		key;

	tmp = 0;
	key = 0;
	if (!fl->width && fl->zero_padd && !fl->zero)
	{
		if (fl->sign < 0 || fl->pos > 0)
		{
			if (fl->sign < 0)
				write(1, "-", 1);
			else
				write(1, "+", 1);
			tmp++;
		}
		fl->width = fl->zero_padd;
		fl->zero_padd = 0;
		fl->zero = 1;
		key = 1;
	}
	ret = ifwhitesp(fl, &tmp, key, ft_strlen(str));
	fl->whitesp = fl->width > ret || fl->pos || fl->sign < 0 ? 0 : fl->whitesp;
	ret += width(str, fl, ret) + tmp + fl->whitesp;
	return (ret);
}

int			parse_d(const char **format, va_list valist, t_flags *fl)
{
	int						ret;
	char					*str;
	__int128_t				nbr;

	nbr = get_nbr_d(FRMT, valist, fl);
	fl->sign = nbr < 0 ? -1 : 1;
	nbr = fl->sign < 0 ? -nbr : nbr;
	str = ft_itoa_ll(nbr);
	fl->zero = fl->zero_padd || (fl->neg && fl->zero) ? 0 : fl->zero;
	*str = nbr == 0 && !fl->zero_padd && fl->dot ? '\0' : *str;
	fl->pos = fl->neg && fl->pos && fl->sign < 0 ? 0 : fl->pos;
	str = fl->sign < 0 && fl->width ? ft_strjoin("-", str, 0, 1) : str;
	str = (fl->pos && fl->neg) || (fl->pos && !fl->neg && fl->width && fl->sign > 0) ?
		ft_strjoin("+", str, 0, 1) : str;
	ret = manage_width(str, fl);
	*FRMT += 1;
	free(str);
	return (ret);
}
