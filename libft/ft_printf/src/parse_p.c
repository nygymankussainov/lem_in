/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:50:18 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/11 14:23:42 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		parse_p(const char **format, va_list valist, t_flags *fl)
{
	int						ret;
	char					*str;
	void					*ptr;

	ret = 0;
	ptr = va_arg(valist, void *);
	str = ft_itoa_base((long long int)ptr, 16);
	str[2] = ptr == 0 && !fl->width && fl->dot ? '\0' : str[2];
	ret = ft_strlen(str);
	if (fl->width < ret && fl->zero_padd)
	{
		write(1, "0x", 2);
		fl->zero_padd -= !ft_strcmp(str, "0x") ? 0 : ret - 2;
		ret += fl->zero_padd > 0 ? fl->zero_padd : 0;
		while (fl->zero_padd > 0 && fl->zero_padd--)
			ft_putchar('0');
		ft_putstr(str + 2);
	}
	else
		ret += width(str, fl, ret);
	*FRMT += 1;
	ft_strdel(&str);
	return (ret);
}
