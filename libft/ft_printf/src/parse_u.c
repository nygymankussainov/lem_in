/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 15:05:38 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/11 14:23:15 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				parse_u(const char **format, va_list valist, t_flags *fl)
{
	int						ret;
	char					*str;
	unsigned long long		nbr;

	ret = 0;
	if (fl->l == 2 || fl->conv == 'U')
		nbr = (long long)va_arg(valist, long long);
	else if (fl->l == 1)
		nbr = (unsigned long)va_arg(valist, unsigned long);
	else if (fl->h == 2)
		nbr = (unsigned char)va_arg(valist, int);
	else if (fl->h == 1)
		nbr = (unsigned short)va_arg(valist, unsigned int);
	else
		nbr = va_arg(valist, unsigned int);
	str = ft_uitoa_base(nbr, 10, 'u');
	fl->zero = fl->zero_padd && fl->width ? 0 : fl->zero;
	*str = nbr == 0 && !fl->zero_padd && fl->dot ? '\0' : *str;
	ret = ft_strlen(str);
	ret += width(str, fl, ret);
	*FRMT += 1;
	ft_strdel(&str);
	return (ret);
}
