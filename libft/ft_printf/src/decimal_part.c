/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 12:14:28 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/11 14:28:38 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_length(char *mant, int exp_i)
{
	int		i;
	int		len;

	i = -exp_i;
	len = 0;
	while (*mant)
	{
		if (*mant == '1')
		{
			len = i;
			if (*(mant + 1) == '\0')
				len++;
		}
		i++;
		mant++;
	}
	if (len == -exp_i)
		return (len);
	else if (len == 0)
		return (-exp_i);
	return (len + 1);
}

void	prepare_number(char *n1, char **res, int exp_i)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(n1);
	while (*n1)
	{
		while (j < -exp_i)
		{
			i++;
			j++;
		}
		(*res)[i] = *n1;
		i++;
		n1++;
	}
}

int		is_all_zeroes(char *mant)
{
	while (*mant)
	{
		if (*mant != '0')
			return (0);
		mant++;
	}
	return (1);
}

void	get_to_first_one(char **mant, int bigl, int *exp_i)
{
	while (**mant != '1')
	{
		(*mant)++;
		(*exp_i)--;
	}
	if (!bigl)
		(*mant)++;
}

int		decimal_part(char **integer, t_float value, t_flags *fl)
{
	int		len;
	char	*res;
	char	*n1;
	char	*tmp_mant;

	if (value.isint && *value.mant && fl->bigl)
		get_to_first_one(&value.mant, fl->bigl, &value.exp_i);
	if ((!*value.mant || is_all_zeroes(value.mant)) && value.exp_i != -1022)
	{
		res = ft_strnew(0);
		return (print(&res, integer, fl, value.sign));
	}
	if (value.isint && *value.mant && !fl->bigl)
		get_to_first_one(&value.mant, fl->bigl, &value.exp_i);
	value.mant += fl->bigl ? 1 : 0;
	if (fl->bigl && value.exp_i != -16382)
		tmp_mant = ft_strjoin(value.mant, "1", 0, 0);
	else
		tmp_mant = ft_strdup(value.mant);
	len = get_length(tmp_mant, value.exp_i);
	res = get_initial_number(len, value.exp_i, &n1);
	value.exp_i--;
	calculate_decimal(tmp_mant, &res, value.exp_i, &n1);
	free(tmp_mant);
	return (print(&res, integer, fl, value.sign));
}
