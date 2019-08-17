/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:44:57 by hfrankly          #+#    #+#             */
/*   Updated: 2019/08/17 11:18:07 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <mlx.h>
# include "./libft/ft_printf/ft_printf.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# define SIZEX 1200
# define SIZEY 1200
# define HALF_W 600

struct s_image;
struct s_mlx;
typedef struct s_room		t_room;
typedef struct s_link		t_link;
typedef struct s_farm		t_farm;

typedef struct				s_room
{
    t_link					*link;
    int						x;
    int						y;
    char					status;
}							t_room;

typedef struct				s_link
{
    int						iroom;
    struct s_link			*next;
}							t_link;

typedef struct				s_farm
{
	int						ants;
	int						room_count;
	int						link_count;
	char					*start;
	char					*end;
	char					*room_name;
	char					*output;
	char					*coords;
	t_room					*room;
}							t_farm;

struct						s_mlx
{
	void					*mlx_ptr;
	void					*win_ptr;
	struct s_image			*image;
};

struct						s_image
{
	void					*image_ptr;
	char					*str;
	int						i;
	int						n;
	int						bpp;
	int						size_line;
	int						endian;
	int						color;
};

int							validation(int fd, t_farm *farm, int isrec, char **line);
int							isint(char *str, t_farm *farm, char c);
char						**validate_links(char *str, t_farm *farm);
char						**validate_rooms(char *str, t_farm *farm);
int							duplicate(t_farm *farm, char **room);
int							isdash(char *str);
#endif
