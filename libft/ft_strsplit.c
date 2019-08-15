/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:35:37 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/05 20:52:32 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **result, size_t word)
{
	while (result[word])
	{
		free(result[word]);
		result[word] = NULL;
		word--;
	}
	free(result);
	result = NULL;
	return (result);
}

static char	**ft_count_letters(char **result, const char *s, char c, char t)
{
	size_t	i;
	size_t	j;
	size_t	let;
	size_t	word;

	word = 0;
	i = 0;
	while (s[i])
	{
		let = 0;
		while (s[i] == c || s[i] == t)
			i++;
		while (s[i] != c && s[i] != t && s[i])
		{
			i++;
			let++;
		}
		if (!(result[word] = ft_memalloc(let + 1)))
			result = ft_free(result, word);
		j = 0;
		while (let)
			result[word][j++] = s[i - let--];
		word++;
	}
	return (result);
}

char		**ft_strsplit(char const *s, char c, char t)
{
	char	**result;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c || s[i] == t)
			i++;
		while (s[i] != c && s[i] != t && s[i])
			i++;
		if (ft_isascii(i - 1) && s[i - 1] != c && s[i - 1] != t)
			j++;
	}
	if (!(result = (char **)malloc(sizeof(char *) * (j + 1))))
		return (NULL);
	result = ft_count_letters(result, s, c, t);
	result[j] = NULL;
	return (result);
}
