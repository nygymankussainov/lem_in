/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_conv_or_whitesp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:52:11 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/11 14:12:52 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			find_conv(const char *format)
{
	while (*FRMT)
	{
		if (*FRMT == 'd' || *FRMT == 'D' || *FRMT == 'i' || *FRMT == 'o'
			|| *FRMT == 'O' || *FRMT == 'u' || *FRMT == 'U' || *FRMT == 'x' || *FRMT == 'X'
			|| *FRMT == 's' || *FRMT == 'F' || *FRMT == 'f' ||
			*FRMT == 'p' || *FRMT == 'c' || *FRMT == '%' || *FRMT == 'h'
			|| *FRMT == 'l' || *FRMT == 'L' || *FRMT == 'b')
			return (1);
		FRMT++;
	}
	return (0);
}

void		find_whitesp(const char **format, t_flags *fl)
{
	while (iswhitesp(**FRMT) || ((**FRMT == '-' || **FRMT == '+')
		&& *(*FRMT + 1) != ft_isdigit(*(*FRMT + 1))))
	{
		if (iswhitesp(**FRMT))
			fl->whitesp++;
		else if (**FRMT == '-')
			fl->neg = 1;
		else if (**FRMT == '+')
			fl->pos = 1;
		(*FRMT)++;
	}
}
