/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 11:50:12 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/16 14:32:14 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static t_gnl_list	*search_fd(t_gnl_list ***list, int fd)
{
	t_gnl_list	*temp;

	temp = **list;
	while (temp)
	{
		if (temp->fd == fd)
		{
			**list = temp;
			return (**list);
		}
		temp = temp->next;
	}
	while (**list)
	{
		if ((**list)->fd == fd)
			return (**list);
		if (!((**list)->prev))
			return (NULL);
		**list = (**list)->prev;
	}
	return (NULL);
}

static t_gnl_list	*create_list(t_gnl_list **list, int fd)
{
	t_gnl_list	*new;

	if (!(search_fd(&list, fd)))
	{
		if (!(new = (t_gnl_list *)ft_memalloc(sizeof(t_gnl_list))))
		{
			free(new);
			new = NULL;
			return (NULL);
		}
		new->fd = fd;
		new->next = NULL;
		if (*list)
		{
			new->next = *list;
			(*list)->prev = new;
		}
		new->prev = NULL;
		*list = new;
	}
	return (*list);
}

static int			isnewline(t_gnl_list **list, char ***line)
{
	size_t	i;

	if (ft_strchr((*list)->str, '\n'))
	{
		(*list)->temp = (*list)->str;
		i = ft_strlen((*list)->str) - ft_strlen(ft_strchr((*list)->str, '\n'));
		**line = ft_strsub((*list)->temp, 0, i);
		if ((*list)->str[i + 1])
			(*list)->str = ft_strdup((*list)->temp + (i + 1));
		else
			(*list)->str = NULL;
		free((*list)->temp);
		(*list)->temp = NULL;
		return (1);
	}
	return (0);
}

int					nonewline(t_gnl_list **list, char ***line)
{
	if (isnewline(list, line) == 1)
		return (1);
	**line = ft_strdup((*list)->str);
	free((*list)->str);
	(*list)->str = NULL;
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	static t_gnl_list	*list;
	char				buf[BUFF_SIZE + 1];

	if (fd < 0 || !line || read(fd, buf, 0) < 0 ||
			!(list = create_list(&list, fd)))
		return (-1);
	while ((list->nbytes = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[list->nbytes] = '\0';
		list->temp = list->str;
		list->str = ft_strjoin(list->temp, buf, 1, 0);
		if (isnewline(&list, &line) == 1)
			return (1);
	}
	if (list->str)
		return (nonewline(&list, &line));
	else
		free(list);
	return (0);
}
