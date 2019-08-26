/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 11:50:12 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/25 15:18:42 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_next_line(const int fd, char **line)
{
	static t_gnl	v;

	v.b = 0;
	if (fd < 0 || (!v.c && !(v.c = ft_strnew(1))) || !line)
		return (-1);
	while (!ft_strchr(v.c, '\n') && (v.b = read(fd, v.buff, BUFF_SIZE)) > 0)
	{
		v.buff[v.b] = '\0';
		v.tmp = v.c;
		v.c = ft_strjoin(v.c, v.buff, 0, 0);
		ft_strdel(&v.tmp);
	}
	if (v.b == -1 || !*(v.tmp = v.c))
		return (v.b == -1 ? -1 : 0);
	if ((v.endl = (ft_strchr(v.c, '\n') > 0)))
		*line = ft_strsub(v.c, 0, ft_strchr(v.c, '\n') - v.c);
	else
		*line = ft_strdup(v.c);
	v.c = ft_strsub(v.c, (unsigned int)(ft_strlen(*line) + v.endl),
			(size_t)(ft_strlen(v.c) - (ft_strlen(*line) + v.endl)));
	ft_strdel(&v.tmp);
	return (!(!v.c && !ft_strlen(*line)));
}
