/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:53:37 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/11 14:22:01 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	get_nbr_x(const char **format, va_list valist,
	t_flags *fl, char **str)
{
	long long	nbr;

	fl->conv = **FRMT;
	if (fl->l == 2)
		nbr = (unsigned long long)va_arg(valist, unsigned long long);
	else if (fl->l == 1)
		nbr = (unsigned long)va_arg(valist, unsigned long);
	else if (fl->h == 2)
		nbr = (unsigned char)va_arg(valist, int);
	else if (fl->h == 1)
		nbr = (unsigned short)va_arg(valist, unsigned int);
	else
		nbr = va_arg(valist, unsigned int);
	if (**FRMT == 'x')
		*str = ft_uitoa_base(nbr, 16, 'x');
	else
		*str = ft_uitoa_base(nbr, 16, 'X');
	return (nbr);
}

void		write_or_join(char **str, char conv, char key)
{
	if (key == 'w')
	{
		if (conv == 'X')
			write(1, "0X", 2);
		else
			write(1, "0x", 2);
	}
	else if (key == 'j')
	{
		if (conv == 'X')
			*str = ft_strjoin("0X", *str, 0, 1);
		else
			*str = ft_strjoin("0x", *str, 0, 1);
	}
}

int			print_0x(char **str, t_flags *fl, int ret, long long nbr)
{
	int		tmp;

	tmp = 0;
	if ((fl->hash && nbr != 0) || (fl->hash && ret >= fl->width && nbr != 0))
	{
		if ((ret >= fl->width && nbr != 0) || (((fl->zero_padd && fl->zero_padd >
			ft_count_digit_ll(nbr, 1)) || fl->zero) && fl->width && fl->hash))
		{
			if (fl->width && fl->hash)
				fl->width -= 2;
			if (fl->width && fl->zero_padd && fl->hash && !fl->neg)
			{
				ft_putchar(' ');
				fl->width--;
				tmp++;
			}
			tmp += 2;
			write_or_join(str, fl->conv, 'w');
		}
		else
			write_or_join(str, fl->conv, 'j');
	}
	return (tmp);
}

int			parse_x(const char **format, va_list valist, t_flags *fl)
{
	int						ret;
	int						tmp;
	char					*str;
	long long				nbr;

	ret = 0;
	tmp = 0;
	nbr = get_nbr_x(FRMT, valist, fl, &str);
	*str = nbr == 0 && !fl->zero_padd && fl->dot ? '\0' : *str;
	fl->neg = fl->hash && fl->width && ft_count_digit_ll(nbr, 1) >= fl->width
		? 0 : fl->neg;
	fl->width = fl->hash && fl->width && ft_count_digit_ll(nbr, 1) >= fl->width
		? 0 : fl->width;
	fl->zero = fl->zero_padd || (fl->hash && fl->zero && fl->neg) ? 0 : fl->zero;
	ret = fl->hash && nbr != 0 ? ft_strlen(str) + 2 : ft_strlen(str);
	tmp = print_0x(&str, fl, ret, nbr);
	ret = manage_width(str, fl) + tmp;
	*FRMT += 1;
	ft_strdel(&str);
	return (ret);
}
