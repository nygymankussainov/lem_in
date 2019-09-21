/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 13:51:24 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/09/20 14:47:32 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "./libft/ft_printf/ft_printf.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_link		t_link;
typedef struct s_room		t_room;
typedef struct s_queue		t_queue;
typedef struct s_qelem		t_qelem;
typedef struct s_path		t_path;

struct						s_queue
{
	t_room					*room;
	t_queue					*next;
};

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

struct						s_room
{
	int						antnbr;
	int						x;
	int						y;
	int						dist;
	int						pathlength;
	int						pathnbr;
	int						pathpart;
	char					*name;
	char					status;
	bool					was;
	bool					visited;
	bool					induplicate;
	bool					outduplicate;
	t_link					*link;
	struct s_room			*in;
	struct s_room			*out;
	struct s_room			*parent;
	struct s_room			*prev;
	struct s_room			*next;
};

struct						s_link
{
	t_room					*room;
	int						weight;
	bool					lock;
	bool					destroy;
	struct s_link			*next;
};

typedef struct				s_hash_tab
{
	t_room					*room;
}							t_hash_tab;

typedef struct				s_farm
{
	int						ants;
	int						room_count;
	int						link_count;
	int						duplicate_count;
	int						start;
	int						end;
	int						recur;
	int						fd;
	int						i;
	char					*line;
	char					*name;
	int						size;
	t_room					*startroom;
	t_room					*endroom;
	t_hash_tab				*h_tab;
	t_hashcodes				*hashcodes;
}							t_farm;

struct						s_path
{
	t_room					*room;
	t_path					*next;
	t_path					*prev;
};

void						free_all_structs(t_hashcodes *hashcodes,
	t_hash_tab *h_tab, t_farm *farm);
int							isroom(char *line);
void						print_valid_data(t_farm *farm, char *argv);
int							isint(char *str, char c);
void						hash_table(t_farm *farm, t_hash_tab *h_tab);
int							hash_func(char *name, int size);
int							validation(t_hash_tab *h_tab, t_farm *farm,
	t_hashcodes **hashcodes);
int							validate_ants(t_farm *farm);
int							validate_rooms(t_hashcodes **hashcodes,
	t_hash_tab *h_tab, t_farm *farm, t_coords **coords);
int							validate_coords(char *line);
int							validate_links(t_hash_tab *h_tab,
	t_farm *farm);
int							write_data_in_sroom(t_farm *farm,
	t_hash_tab *h_tab, t_hashcodes **hashcodes, t_coords **coords);
void						write_hashcode_in_struct(int hash,
	t_hashcodes **hashcodes);
int							find_and_connect_rooms(char *line,
	t_hash_tab *h_tab, int size);
void						free_coords(t_coords **coords);
int							islink(char *line);
int							isduplicate(t_coords *coords);
int							count_space(char *line);
t_link						*create_slink(t_room *room, char *linkname);
int							count_room(char *argv);
int							isroom(char *line);
void						print_links(t_hashcodes *hashcodes,
	t_hash_tab *h_tab);
int							bfs(t_farm *farm);
t_room						*find_startend(t_room *room, char c);
void						dequeue(t_queue **queue);
void						enqueue(t_queue **queue, t_room *room, t_queue **last);

int							find_shortest_path(t_farm *farm, int ret);
void						unvisit_rooms(t_farm *farm);
int							is_free_path(t_farm *farm);
t_room						*ft_return_room(t_farm *farm, char *name);
int							ft_reverse_shortest_path(t_farm *farm, int pathnbr);
void						ft_make_room_duplicate(t_room *room);
void						ft_make_rooms_duplicates(t_farm *farm);
void						lem_in(t_farm *farm);
void						ft_show_pathlengthes(t_farm *farm);
void						ft_create_in_link(t_room *in, t_link **linkin, t_room *linkroom, t_room *nextroom);
void						ft_create_out_link(t_room *out, t_link **linkout, t_room *linkroom, t_room *nextroom);
t_room						*ft_find_next_room(t_room *room);
void						ft_create_out_link_if_nextroom(t_room *out, t_link **linkout, t_room *linkroom);
t_room						*ft_roomcpy(t_room *room);
void						ft_init_duplicates(t_room **room, t_link **linkout, t_link **linkin);
void    					ft_send_ants_algo(t_farm *farm, int pathcount);
void						ft_connect_in_and_out(t_link **linkout, t_link **linkin, t_room *room);
t_path						**ft_pickout_pathes(t_farm *farm, int pathcount);
t_path						*ft_get_path(t_farm *farm, t_room *room);
t_link						*ft_get_next_link(t_room *room);
bool						ft_if_destroy(t_room *room1, t_room *room2);
void						ft_refresh_graph(t_farm *farm);
t_room						*ft_room_refresh(t_room *room);
void						ft_link_refresh(t_room *room, t_room *linkroom, t_link *link);
void						ft_change_vars(t_room **room, t_room **linkroom);
void						ft_connect_with_parent(t_room *src, t_room *dst);
void						ft_free_room(t_room **room);

#endif

// it's not necessary to duplicate rooms every time
