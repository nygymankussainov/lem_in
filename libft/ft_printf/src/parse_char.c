/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_symbol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 10:27:31 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/11 14:35:05 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_string(va_list valist, t_flags *fl)
{
	char	*str;
	int		ret;
	int		tmp;

	str = va_arg(valist, char *);
	if (!str)
		str = fl->dot && !fl->zero_padd ? ft_strdup("(null).") :
			ft_strdup("(null)");
	else
		str = ft_strndup(str, ft_strlen(str));
	*str = fl->dot && !fl->zero_padd ? '\0' : *str;
	ret = ft_strlen(str);
	if (fl->zero_padd && fl->zero_padd <= ret)
	{
		str[fl->zero_padd] = '\0';
		tmp = ret;
		ret = ret - tmp + ft_strlen(str);
	}
	else
		fl->zero_padd = 0;
	if (ret >= fl->width)
		ft_putstr(str);
	ret += ret < fl->width ? width(str, fl, ret) : 0;
	ft_strdel(&str);
	return (ret);
}

int		parse_char(const char **format, va_list valist, t_flags *fl)
{
	char	*str;
	char	sym;
	int		ret;

	ret = 1;
	fl->conv = **FRMT;
	fl->zero = 0;
	if (fl->conv == 's')
		ret = print_string(valist, fl);
	else
	{
		sym = (char)va_arg(valist, int);
		str = ft_strnew(1);
		str[0] = sym;
		if (ret >= fl->width || ((fl->neg || ret >= fl->width)
			&& !sym && fl->width))
			ft_putchar(sym);
		ret += ret < fl->width ? width(str, fl, ret) : 0;
		if (!sym && fl->width && (ret <= fl->width || !fl->neg))
			write(1, &sym, 1);
		ft_strdel(&str);
	}
	*FRMT += 1;
	return (ret);
}
