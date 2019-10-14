/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 13:51:24 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/14 19:51:14 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "vizualizer/includes/visual.h"
# include "libft/ft_printf/ft_printf.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_link		t_link;
typedef struct s_room		t_room;
typedef struct s_queue		t_queue;
typedef struct s_path		t_path;

struct						s_queue
{
	int						index;
	int						steps;
	t_room					*room;
	t_queue					*next;
	t_queue					*prev;
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
	int						path;
	int						antnbr;
	int						x;
	int						y;
	int						dist;
	char					*name;
	char					status;
	bool					visited;
	t_link					*link;
	bool					dup;
	bool					in;
	bool					out;
	struct s_room			*outroom;
	struct s_room			*inroom;
	struct s_room			*prev;
	struct s_room			*next;
};

struct						s_link
{
	t_room					*room;
	int						weight;
	bool					lock;
	bool					go;
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
	int						start;
	int						end;
	int						recur;
	int						fd;
	int						ret;
	int						i;
	char					*line;
	char					*name;
	int						size;
	int						path_nb;
	int						max_paths;
	t_path					*path;
	t_queue					*onestep_path;
	t_room					*endroom;
	t_room					*startroom;
	t_hash_tab				*h_tab;
	t_hashcodes				*hashcodes;
}							t_farm;

struct						s_path
{
	int						index;
	int						steps;
	int						lines;
	bool					checked;
	int						size;
	t_queue					*list;
	t_queue					*endlist;
	t_path					*next;
};

void						free_all_structs(t_hashcodes *hashcodes,
	t_hash_tab *h_tab, t_farm *farm);
int							isroom(char *line);
void						print_valid_data(t_farm *farm);
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
int							count_room(char c);
int							bfs(t_farm *farm, t_path **path);
void						dequeue(t_queue **queue);
void						enqueue(t_queue **queue,
	t_room *room, t_queue **last);
int							find_shortest_path(t_farm *farm,
	t_path **path, int ret);
void						unvisit_rooms(t_farm *farm, int i);
int							bellman_ford(t_farm *farm, t_path *path);
int							ft_count_paths(t_farm *farm);
void						run_ants(t_farm *farm, t_path *path);
void						ft_show_array(int *arr, int size);
int							sort_paths(t_farm *farm, t_path **path, int size);
void						sort_arr_path(t_path *path, int size);
void						create_queue_of_paths(t_queue *queue, t_path *path,
	t_room *room, int size);
void						sort_arr_path(t_path *path, int size);
void						reindex_paths(t_path *path);
int							count_paths(t_queue *queue, t_room *room,
	t_queue *last, t_farm *farm);
void						check_link(t_queue *list);
int							create_paths(t_farm *farm, t_path **path);
int							count_short_paths(t_path *path);
void						create_dup_rooms(t_path *path);
int							delete_dup_rooms(t_path *path);
int							is_need_more_paths(int ants, t_path **path);
void						manage_direction(t_path *path, int i);
void						make_path_directed(t_path *path);
void						find_disjoint_paths(t_path **path);
void						create_list_of_paths(t_room *room,
	t_path *path, int i);
void						enqueue_to_begin(t_queue **queue, t_room *room);
void						free_paths(t_path **path);
void						change_link_room(t_queue *list);
void						change_prev_rooms(t_room *room);
t_path						*create_new_arr_path(t_farm *farm, int size);
t_link						*get_start_end_link(t_queue *list);
void						delete_path(t_path *path, int noend);
void						check_paths(t_path *path);
void						push_ant(t_queue *list, int ant);
void						push_ant_further(t_queue *list);
int							count_optimal_paths(t_path *path, int ants);
int							expression(t_path *path, int i);
int							create_paths(t_farm *farm, t_path **path);

#endif
