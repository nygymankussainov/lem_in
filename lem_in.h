/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 13:51:24 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/27 21:09:32 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "./libft/ft_printf/ft_printf.h"
# include <fcntl.h>
# include <stdio.h>

# define H_SIZE 100136400

typedef struct s_link		t_link;

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

typedef struct				s_room
{
	int						antnbr;
	int						x;
	int						y;
	int						weight;
	int						bfs_lvl;
	char					*name;
	char					status;
	t_link					*link;
	struct s_room			*next;
}							t_room;

typedef struct				s_link
{
	t_room					*room;
	struct s_link			*next;
}							t_link;

typedef struct				s_hash_tab
{
	t_room					*room;
}							t_hash_tab;

typedef struct				s_farm
{
	int						ants;
	int						room_count;
	int						link_count;
	int						start;
	int						end;
	int						recur;
	int						fd;
	int						i;
	char					*line;
	char					*name;
	t_hash_tab				*h_tab;
	t_hashcodes				*hashcodes;
}							t_farm;

int							isint(char *str, char c);
void						hash_table(t_farm *farm, t_hash_tab *h_tab);
int							hash_func(char *name);
int							validation(t_hash_tab *h_tab, t_farm *farm,
	t_hashcodes **hashcodes);
int							validate_ants(t_farm *farm);
int							validate_rooms(t_hashcodes **hashcodes,
	t_hash_tab *h_tab, t_farm *farm, t_coords **coords);
int							validate_coords(char *line);
int							validate_links(t_hash_tab *h_tab,
	t_farm *farm, t_hashcodes *hashcodes);
int							write_data_in_sroom(t_farm *farm,
	t_hash_tab *h_tab, t_hashcodes **hashcodes, t_coords **coords);
void						write_hashcode_in_struct(int hash,
	t_hashcodes **hashcodes);
int							find_and_connect_rooms(char *line,
	t_hash_tab *h_tab, t_hashcodes *hashcodes);
void						free_coords(t_coords **coords);
int							islink(char *line);
int							isduplicate(t_coords *coords);
int							is_room_exist(int hash, t_hashcodes *hashcodes);
int							count_space(char *line);
t_link						*create_slink(t_room *room, char *linkname);

#endif
