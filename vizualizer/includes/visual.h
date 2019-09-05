/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:44:57 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/05 19:18:50 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include "../../lem_in.h"
# include "/Users/vhazelnu/.brew/Cellar/sdl2/2.0.10/include/SDL2/SDL.h"
# include <fcntl.h>
# include <math.h>

# define SIZEX 1200
# define SIZEY 1200
# define ABS(x) ((x < 0) ? -1 * x : x)

typedef	struct s_sdl		t_sdl;
typedef	struct s_image		t_image;
typedef	struct s_map		t_map;
typedef struct s_line		t_line;
typedef struct s_point		t_point;
typedef struct s_ant		t_ant;

typedef struct s_room		t_room;
typedef struct s_link		t_link;
typedef struct s_farm		t_farm;

struct 		s_map
{
	int				maxdif;
	int				xcenter;
	int				ycenter;
};

struct s_sdl
{
	SDL_Window		*win;
	SDL_Surface		*sfc;
	SDL_Texture		*text;
	SDL_Renderer	*ren;
	SDL_Event		*e;
	char			**cmdline;
	int				stepsize;
	int				arrsize;
	int				fd;
	struct s_ant	*ants;
	struct s_farm	*farm;
	struct s_map	map;
};

struct		s_point
{
	float			x;
	float			y;
	float			z;
	float			x0;
	float			y0;
	float			z0;
	int				color;
};

struct		s_line
{
	t_point			p0;
	t_point			p1;
	t_point			current;
	int				ydir;
	int				xdir;
	float			k;
};

struct		s_ant
{
	int				x;
	int				y;
	int				antnbr;
	t_room			*srcroom;
	t_room			*dstroom;
	int				radius;
};


void		ft_bresenham(t_sdl *sdl, int *coord);
void		ft_line_init(t_line *line, t_point *delta);
void		ft_swap_floats(float *a, float *b);
//coords.c
int			ft_find_max_infarm(t_farm *farm, char c);
int			ft_find_min_infarm(t_farm *farm, char c);
int			*ft_find_maxcoords(t_farm *farm);
t_map		ft_initmap(t_farm *farm, int *maxcoords);
void		ft_change_coords(t_sdl *sdl);
//draw.c
void		ft_draw_vertex(t_sdl *sdl, const t_room *room, int room_count);
void		ft_draw_link(t_sdl *sdl, const t_room *room);
void		ft_draw_graph(t_sdl *sdl);
void		ft_draw_circle(SDL_Renderer *ren, int x, int y, int r);
void		ft_draw_rooms(t_sdl *sdl);
//putants.c
void		ft_move_ant(t_sdl *sdl, t_ant *ant, int step);
//vizualizer.c
void		ft_get_ants(t_sdl *sdl);
void		ft_send_ants(t_sdl *sdl, int *length);
int			ft_do_move(t_sdl *sdl);
int			ft_go_ant(t_sdl *sdl);
void		vizualizer(t_farm *farm);
//vizualizer1.c
int			ft_get_link_length(const t_room *src, const t_room *dst);
t_room		*ft_find_ant_room(t_farm *farm, char *str);
//sdl.c
int			ft_init_sdl(t_sdl *sdl);
void		ft_close_sdl(t_sdl *sdl);
//main.c
int			ft_array_size(char **arr);
void		free_arr(char **str);

#endif
