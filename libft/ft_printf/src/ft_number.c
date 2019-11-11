/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 14:20:32 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/11 14:14:12 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_number(const char **format, va_list valist, t_flags *fl)
{
	int		ret;

	ret = 0;
	fl->conv = **FRMT;
	if (**FRMT == 'd' || **FRMT == 'D' || **FRMT == 'i')
		ret = parse_d(FRMT, valist, fl);
	else if (**FRMT == 'x' || **FRMT == 'X')
		ret = parse_x(FRMT, valist, fl);
	else if (**FRMT == 'o' || **FRMT == 'O')
		ret = parse_o(FRMT, valist, fl);
	else if (**FRMT == 'u' || **FRMT == 'U')
		ret = parse_u(FRMT, valist, fl);
	else if (**FRMT == 'p')
		ret = parse_p(FRMT, valist, fl);
	else if (**FRMT == 'f' || **FRMT == 'F' || **FRMT == 'b')
		ret = parse_f(FRMT, valist, fl);
	return (ret);
}
