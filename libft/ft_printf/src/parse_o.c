/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_o.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:51:47 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/11 14:22:45 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		parse_o(const char **format, va_list valist, t_flags *fl)
{
	int						ret;
	char					*str;
	unsigned long long		nbr;

	ret = 0;
	if (fl->l == 2 || fl->conv == 'O')
		nbr = (long long)va_arg(valist, long long);
	else if (fl->l == 1)
		nbr = (long)va_arg(valist, long);
	else if (fl->h == 2)
		nbr = (unsigned char)va_arg(valist, int);
	else if (fl->h == 1)
		nbr = (unsigned short)va_arg(valist, unsigned int);
	else
		nbr = va_arg(valist, unsigned int);
	str = ft_uitoa_base(nbr, 8, 'o');
	*str = nbr == 0 && !fl->zero_padd && fl->dot ? '\0' : *str;
	if (fl->hash && (nbr != 0 || (fl->dot && nbr == 0)))
		str = ft_strjoin("0", str, 0, 1);
	fl->zero = fl->zero_padd || (fl->neg && fl->zero) ? 0 : fl->zero;
	ret = fl->hash ? ft_strlen(str) + 1 : ft_strlen(str);
	ret = manage_width(str, fl);
	*FRMT += 1;
	ft_strdel(&str);
	return (ret);
}
