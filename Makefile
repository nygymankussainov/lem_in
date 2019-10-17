# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:51 by vhazelnu          #+#    #+#              #
#    Updated: 2019/10/17 15:10:09 by vhazelnu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ARCHIVE = libftlemin.a

NAME = lem-in

LIB = libft/ft_printf
LIB_A = libft/libft.a $(LIB)/libftprintf.a 
VISUAL = ./vizualizer

INCLUDES = -I ./

SOURCES_VAL = isint.c validation.c validate_rooms.c write_data_in_sroom.c validate_links.c validate_ants.c \
	work_with_data.c validate_coords.c find_and_connect_rooms.c \

SOURCES = lem_in.c hash_func.c bfs.c bellman_ford.c run_ants.c unvisit_rooms.c delete_dup_rooms.c \
		sort_paths.c create_new_arr_path.c create_paths.c create_dup_rooms.c push_ant.c print_graph.c lock_collided_links.c \
		manage_directions.c is_need_more_paths.c change_link_room.c count_optimal_paths.c \

OBJDIR = obj

SRC_VAL = $(addprefix src/validation/, $(SOURCES_VAL))
SRC = $(addprefix src/, $(SOURCES))

OBJ_VAL = $(patsubst %.c, %.o, $(SOURCES_VAL))
OBJ = $(patsubst %.c, %.o, $(SOURCES))

CCFL = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: obj_dir $(ARCHIVE) $(NAME)

$(ARCHIVE): $(OBJ_VAL) $(OBJ)
	@make -sC $(LIB)
	# @make -C $(VISUAL)
	@ar rc $(ARCHIVE) $(OBJ_VAL) $(OBJ)
	@ranlib $(ARCHIVE)

%.o: %.c
	@gcc $(CCFL) -c $(INCLUDES) $<

$(NAME):
	@gcc $(CCFL) -o $(NAME) $(ARCHIVE) $(LIB_A)
	@echo lem_in is compiled!

obj_dir:
	@mkdir -p $(OBJDIR)

clean:
	@make clean -C $(LIB)
	@rm -f $(ARCHIVE)
	@rm -f $(NAME)
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LIB)
	@make fclean -C $(VISUAL)

re: fclean all
