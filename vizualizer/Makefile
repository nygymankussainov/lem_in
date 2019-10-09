# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:51 by vhazelnu          #+#    #+#              #
#    Updated: 2019/10/09 22:56:46 by hfrankly         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = visual

SDL = -L ~/.brew/Cellar/sdl2/2.0.10/lib -l SDL2-2.0.0 \
		`sdl2-config --libs` -lSDL2_gfx -lSDL2_mixer -lSDL2_ttf -lm

LIB = ../libft/ft_printf
LIB_A = ../libft/libft.a $(LIB)/libftprintf.a 

INCLUDES = -I../libft -I./includes -I./includes/SDL2 -I./includes/SDL2_GFX -I./includes/SDL2_MIX `sdl2-config --cflags`

SRCS =	../src/hash_func.c ../src/validation/validate_coords.c ../src/validation/find_and_connect_rooms.c ../src/bfs.c ../src/bellman_ford.c ../src/run_ants.c ../src/unvisit_rooms.c ../src/delete_dup_rooms.c \
		../src/validation/isint.c ../src/validation/validation.c ../src/validation/validate_rooms.c ../src/validation/write_data_in_sroom.c ../src/validation/validate_links.c ../src/validation/validate_ants.c \
		../src/validation/work_with_data.c ../src/qsort.c ../src/create_new_arr_path.c ../src/create_paths.c ../src/create_dup_rooms.c ../src/push_ant.c \
		../src/find_disjoint_paths.c ../src/manage_directions.c ../src/is_need_more_paths.c ../src/change_prev_rooms.c ../src/check_paths.c ../src/count_optimal_paths.c \
		srcs/get_ants.c srcs/main.c srcs/coords.c srcs/draw.c srcs/putants.c srcs/vizualizer.c srcs/sdl.c srcs/coords1.c

OBJ = $(SRCS:.c=.o)

CCFL = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c $(INCLUDES)
	@gcc -Wall -Wextra -Werror $(INCLUDES) -c $<

$(NAME): $(OBJ)
	@gcc $(CCFL) -o ../$(NAME) $(INCLUDES) $(SDL) $(SRCS) $(LIB_A)

clean:
	@make clean -C $(LIB)
	@rm -f $(ARCHIVE)
	@rm -f ../$(NAME)
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LIB)

re: fclean all
