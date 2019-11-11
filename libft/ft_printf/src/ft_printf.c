/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 12:57:32 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/11 14:38:23 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

short		flag_length(char *str, char c)
{
	short	i;

	i = 0;
	while (*str)
	{
		if (*str == c)
			i++;
		str++;
	}
	return (i);
}

void		get_flags(const char *format, int i, t_flags *fl)
{
	char		*str;

	str = ft_strnew(i + 1);
	str = ft_strncpy(str, FRMT, i + 1);
	str[i + 1] = '\0';
	i = 0;
	while (str[i])
	{
		fl->prec = str[i] == '.' ? ft_atoi(str + i + 1) : fl->prec;
		fl->zero_padd = str[i] == '.' ? ft_atoi(str + i + 1) : fl->zero_padd;
		fl->dot = str[i] == '.' ? 1 : fl->dot;
		fl->hash = str[i] == '#' ? 1 : fl->hash;
		fl->zero = str[i] == '0' && !ft_isalpha(str[i + 1]) ? 1 : fl->zero;
		fl->neg = str[i] == '-' ? 1 : fl->neg;
		fl->pos = str[i] == '+' ? 1 : fl->pos;
		fl->bigl = str[i] == 'L' ? 1 : fl->bigl;
		fl->z = str[i] == 'z' ? 1 : fl->z;
		i++;
	}
	fl->width += get_width(str);
	fl->m = flag_length(str, 'm');
	fl->z = fl->m ? 0 : fl->z;
	fl->l = flag_length(str, 'l');
	fl->h = flag_length(str, 'h');
	ft_strdel(&str);
}

int			parse_conv(const char **format, va_list valist, t_flags *fl)
{
	int		ret;

	ret = 0;
	fl->zero = fl->neg && (**FRMT == 'f' || **FRMT == 'F') ? 0 : fl->zero;
	if (ft_strchr("diouxXpfFDOUb", **FRMT) && *FRMT)
		ret = ft_number(FRMT, valist, fl);
	else if (ft_strchr("sc", **FRMT) && **FRMT)
		ret = parse_char(FRMT, valist, fl);
	else
	{
		fl->zero = fl->neg ? 0 : fl->zero;
		if (fl->width && !fl->neg)
			ret = print_zero_or_space(--fl->width, fl->zero, ret);
		ft_putchar(**FRMT);
		if (fl->width && fl->neg)
			ret = print_zero_or_space(--fl->width, fl->zero, ret);
		*FRMT += 1;
		ret++;
	}
	free(fl);
	return (ret);
}

int			parsing(const char **format, va_list valist)
{
	int			i;
	t_flags		*fl;

	if (!(fl = (t_flags *)ft_memalloc(sizeof(t_flags))))
		exit(12);
	i = 0;
	(*FRMT)++;
	find_whitesp(FRMT, fl);
	fl->whitesp = fl->whitesp > 1 ? 1 : fl->whitesp;
	fl->prec = 6;
	while (ft_strchr(".-+#lLh0123456789mz", *(*FRMT + i)) && *(FRMT + i))
		i++;
	if (i)
		get_flags(*FRMT, i, fl);
	if (find_conv(*FRMT))
		*FRMT += i;
	else
	{
		free(fl);
		return (0);
	}
	return (parse_conv(FRMT, valist, fl));
}

int			ft_printf(const char *format, ...)
{
	int			ret;
	va_list		valist;

	va_start(valist, FRMT);
	ret = 0;
	while (*FRMT)
	{
		if (*FRMT == '%')
			ret += parsing(&FRMT, valist);
		else
		{
			ft_putchar(*FRMT);
			FRMT++;
			ret++;
		}
	}
	va_end(valist);
	return (ret);
}
