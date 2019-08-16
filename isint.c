/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:33:43 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/16 15:46:55 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		isint_limit(char *str)
{
	size_t		i;
	long long	result;

	i = 0;
	result = 0;
	while ((str[i] != '\0') && (str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + str[i] - '0';
		if (result > 2147483647)
			return (0);
		i++;
	}
	return (1);
}

int		isonlynum(char *str, char c)
{
	int		i;

	i = 0;
	if (str[0] == '-')
		return (0);
	while (str[i])
	{
		if (ft_isascii(str[i]) && !ft_isdigit(str[i]) && !iswhitesp(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int		isint(char *str, t_farm *farm, char c)
{
	int		i;
	int		sign;

	i = 0;
	sign = 0;
	if (str[0] == '+' || (str[0] == '-' && c == 'r'))
		str++;
	if (!str[0])
		return (0);
	if (str[0] == '0' && str[1])
		while (*str == '0' && *str)
			str++;
	if (!isonlynum(str, c))
		return (0);
	i = ft_strlen(str);
	if (i > 10)
		return (0);
	else if (i == 10)
		return(isint_limit(str));
	return (1);
}
