/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:33:43 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/17 14:07:37 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		isint_limit(char *str)
{
	size_t		i;
	int			sign;
	long long	result;

	i = 0;
	result = 0;
	sign = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		sign = -1;
		i++;
	}
	while ((str[i] != '\0') && (str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + str[i] - '0';
		if ((result > 2147483647 && !sign) || (result > 2147483648 && sign))
			return (0);
		i++;
	}
	return (1);
}

int		isonlynum(char *str, char c)
{
	int		i;

	i = 0;
	if (str[0] == '-' || (str[0] == '0' && !str[1] && c == 'a'))
		return (0);
	while (str[i])
	{
		if (c == 'r' && ft_isascii(str[i]) &&
			!ft_isdigit(str[i]) && !iswhitesp(str[i]))
			return (0);
		else if (c == 'a' && ft_isascii(str[i]) &&
			!ft_isdigit(str[i]) && iswhitesp(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int		isint(char *str, char c)
{
	int		len;
	int		sign;

	sign = str[0] == '-' && c == 'r' ? -1 : 0;
	if (str[0] == '+' || (str[0] == '-' && c == 'r'))
		str++;
	if (!str[0])
		return (0);
	if (str[0] == '0' && str[1])
		while (*str == '0' && *str)
			str++;
	if (!isonlynum(str, c))
		return (0);
	str -= sign == -1 ? 1 : 0;
	*str = sign == -1 && *str != '-' ? '-' : *str;
	len = ft_strlen(str);
	if (len > 10 && !sign)
		return (0);
	else if (len >= 10 || (len >= 11 && sign))
	{
		if (!isint_limit(str))
			return (0);
		*str = *(str - 1) == '0' && *str == '-' ? '0' : *str;
	}
	return (1);
}
