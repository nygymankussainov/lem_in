/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 11:02:01 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/11 15:40:23 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define FRMT format

# include "libft.h"
# include <stdio.h>
# include <stdarg.h>

typedef struct		s_float
{
	char			*binary;
	short			sign;
	char			*exp;
	char			*mant;
	long double		db;
	int				exp_i;
	int				mant_i;
	short			isint;
}					t_float;

typedef struct		s_flags
{
	int				zero_padd;
	int				prec;
	int				width;
	int				whitesp;
	int				sign;
	char			conv;
	short			dot;
	short			bigl;
	short			h;
	short			l;
	short			m;
	short			z;
	short			zero;
	short			pos;
	short			neg;
	short			hash;
}					t_flags;

int					ft_printf(const char *format, ...);
int					find_conv(const char *s);
void				find_whitesp(const char **format, t_flags *fl);
int					parse_s(const char **format, va_list valist, t_flags *fl);
int					parse_c(const char **format, va_list valist, t_flags *fl);
int					parse_o(const char **format, va_list valist, t_flags *fl);
int					parse_p(const char **format, va_list valist, t_flags *fl);
int					parse_x(const char **format, va_list valist, t_flags *fl);
int					parse_d(const char **format, va_list valist, t_flags *fl);
int					parse_u(const char **format, va_list valist, t_flags *fl);
int					parse_f(const char **format, va_list valist, t_flags *fl);
int					parse_b(t_flags *fl, t_float value);
int					ft_number(const char **format, va_list valist, t_flags *fl);
int					parse_char(const char **format, va_list valist, t_flags *fl);
int					get_width(char *str);
int					width_for_float(char *str, t_flags *fl, int ret);
int					width(char *str, t_flags *fl, int len);
int					manage_width(char *str, t_flags *fl);
int					print_zero_or_space(int width, int zero, int ret);
int					integer_part(t_float value, t_flags *fl);
int					decimal_part(char **integer, t_float value, t_flags *fl);
void				prepare_number(char *n1, char **res, int exp_i);
void				calculate_decimal(char *mant, char **res, int exp_i,
	char **n1);
char				*get_initial_number(int len, int exp_i, char **n1);
int					print(char **decimal, char **integer, t_flags *fl,
	int sign);
int					get_width(char *str);
void				longadd(char *s1, char *s2, char **res2);
void				longmulti(char *a, const char *b, char **c);
void				longdiv(char *number, int divisor, char **res);

#endif
