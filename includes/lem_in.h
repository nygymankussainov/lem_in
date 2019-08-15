/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:44:57 by hfrankly          #+#    #+#             */
/*   Updated: 2019/08/15 15:47:51 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "mlx.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# define SIZEX 1200
# define SIZEY 1200
# define HALF_W 600

typedef	struct s_image		t_image;
typedef	struct s_mlx		t_mlx;
typedef struct s_room		t_room;
typedef struct s_link		t_link;

typedef struct  s_room
{
    t_link *link;
    int x;
    int y;
    char status;
}               t_room;

typedef struct s_link
{
    int iroom;
    struct s_link *next;
}				t_link;

struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_image	image;
};

struct	s_image
{
	void		*image_ptr;
	char		*str;
	int			i;
	int			n;
	int			bpp;
	int			size_line;
	int			endian;
	int			color;
};

#endif

