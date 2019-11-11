/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 19:27:34 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/11 14:19:41 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_width(char *str)
{
	int width;
	int	i;

	i = 0;
	while (*str && *str != '.')
	{
		if (ft_isdigit(*str))
		{
			while (str[i] && str[i] != '.' && !ft_isalpha(str[i]))
			{
				if (str[i] == '-' || str[i] == '+')
				{
					width = ft_atoi(str + i + 1);
					width = width < 0 ? -width : width;
					return (width);
				}
				i++;
			}
			width = ft_atoi(str);
			width = width < 0 ? -width : width;
			return (width);
		}
		str++;
	}
	return (0);
}

void	put_zero_or_space(char **str, int width, int zero)
{
	while (width > 0 && width--)
	{
		if (zero)
		{
			if ((*str)[0] == '-' || (*str)[0] == '+')
			{
				if ((*str)[0] == '-')
					write(1, "-", 1);
				else
					write(1, "+", 1);
				(*str)++;
			}
			ft_putchar('0');
		}
		else
			ft_putchar(' ');
	}
}

void	put_zero_padding(char **str, int zero_padd)
{
	while (zero_padd > 0 && zero_padd--)
	{
		if ((*str)[0] == '-' || (*str)[0] == '+')
		{
			if ((*str)[0] == '-')
				write(1, "-", 1);
			else
				write(1, "+", 1);
			(*str)++;
		}
		ft_putchar('0');
	}
}

void	manage_order_and_print(char *str, t_flags *fl)
{
	if (!fl->neg)
	{
		put_zero_or_space(&str, fl->width, fl->zero);
		if (fl->neg && !fl->pos && !fl->zero_padd)
			ft_putstr(str);
		put_zero_padding(&str, fl->zero_padd);
		if (fl->pos || !fl->neg)
			ft_putstr(str);
	}
	else
	{
		put_zero_padding(&str, fl->zero_padd);
		if ((fl->neg && !fl->pos) || (fl->neg && fl->pos))
			ft_putstr(str);
		put_zero_or_space(&str, fl->width, fl->zero);
		if (fl->pos && !fl->neg)
			ft_putstr(str);
	}
}

int		width(char *str, t_flags *fl, int len)
{
	int		ret;

	ret = 0;
	if (fl->pos && fl->sign > 0 && !fl->width)
		write(1, "+", 1);
	if (fl->sign < 0 && !fl->width)
		write(1, "-", 1);
	ret += (fl->pos && fl->sign > 0 && !fl->width) ||
		(fl->sign < 0 && !fl->width) ? 1 : 0;
	fl->zero_padd += (fl->pos && fl->neg) || (fl->zero_padd > 0 &&
		fl->sign < 0 && fl->width) ? 1 : 0;
	fl->zero_padd += fl->pos && !fl->neg && fl->width && fl->sign > 0 ? 1 : 0;
	fl->zero_padd -= fl->zero_padd > 0 ? len : 0;
	fl->width -= fl->zero_padd > 0 ? len + fl->zero_padd : len;
	ret = fl->width > 0 ? fl->width : ret;
	ret += fl->zero_padd > 0 ? fl->zero_padd : 0;
	manage_order_and_print(str, fl);
	return (ret);
}
