/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 13:51:24 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/26 13:52:32 by vhazelnu         ###   ########.fr       */
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

typedef struct				s_hashcodes
{
	int						hash_code;
	struct s_hashcodes		*next;
}							t_hashcodes;

typedef struct				s_coords
{
	int						x;
	int						y;
	struct s_coords			*next;
}							t_coords;

typedef struct				s_link
{
	char					*name;
	struct s_link			*next;
}							t_link;

typedef struct				s_room
{
	int						x;
	int						y;
	char					*name;
	char					status;
	t_link					*link;
	struct s_room			*next;
}							t_room;

typedef struct				s_farm
{
	int						ants;
	int						room_count;
	int						link_count;
	int						isst;
	int						isend;
	int						isrec;
	int						fd;
	int						i;
	char					*line;
	char					*name;
}							t_farm;

typedef struct				s_mlx
{
	void					*mlx_ptr;
	void					*win_ptr;
	struct s_image			*image;
}							t_mlx;

typedef struct				s_image
{
	void					*image_ptr;
	char					*str;
	int						i;
	int						n;
	int						bpp;
	int						size_line;
	int						endian;
	int						color;
}							t_image;

int							isint(char *str, char c);
void						hash_table(t_farm *farm, t_room **room);
int							hash_func(char *name);
int							validation(t_room **room, t_farm *farm,
	t_hashcodes **hashcodes);
int							validate_ants(t_farm *farm);
int							validate_rooms(t_hashcodes **hashcodes,
	t_room **room, t_farm *farm, t_coords **coords);
int							validate_coords(char *line);
int							validate_links(t_room **room,
	t_farm *farm, t_hashcodes *hashcodes);
int							write_data_in_sroom(t_farm *farm,
	t_room **room, t_hashcodes **hashcodes, t_coords **coords);
void						write_hashcode_in_struct(int hash,
	t_hashcodes **hashcodes);
int							find_and_connect_rooms(char *line,
	t_room **room, t_hashcodes *hashcodes);
void						free_coords(t_coords **coords);
int							islink(char *line);
int							isduplicate(t_coords *coords);
int							is_room_exist(int hash, t_hashcodes *hashcodes);
int							count_space(char *line);
t_link						*create_slink(t_room *room, char *linkname);

#endif
