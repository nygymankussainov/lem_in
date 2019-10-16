# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:51 by vhazelnu          #+#    #+#              #
#    Updated: 2019/10/16 16:24:02 by vhazelnu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ARCHIVE = libftlemin.a

NAME = lem-in

LIB = libft/ft_printf
LIB_A = libft/libft.a $(LIB)/libftprintf.a 
VISUAL = ./vizualizer

INCLUDES = -I ./libft -I ./libft/ft_printf/

SOURCES = lem_in.c hash_func.c validation/validate_coords.c validation/find_and_connect_rooms.c bfs.c bellman_ford.c run_ants.c unvisit_rooms.c delete_dup_rooms.c \
		validation/isint.c validation/validation.c validation/validate_rooms.c validation/write_data_in_sroom.c validation/validate_links.c validation/validate_ants.c \
		validation/work_with_data.c sort_paths.c create_new_arr_path.c create_paths.c create_dup_rooms.c push_ant.c print_graph.c lock_collided_links.c \
		manage_directions.c is_need_more_paths.c change_link_room.c count_optimal_paths.c \

SRC = $(addprefix src/, $(SOURCES))

OBJ = $(patsubst %.c, %.o, $(SRC))

CCFL = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(ARCHIVE) $(NAME)

$(ARCHIVE): $(OBJ)
	@make -C $(LIB)
	# @make -C $(VISUAL)
	@ar rc $(ARCHIVE) $(OBJ)
	@ranlib $(ARCHIVE)

%.o: %.c $(INCLUDES)
	@gcc $(CCFL) -c $<

$(NAME): $(OBJ)
	@gcc $(CCFL) -o $(NAME) $(ARCHIVE) $(LIB_A)

clean:
	@make clean -C $(LIB)
	@rm -f $(ARCHIVE)
	@rm -f $(NAME)
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LIB)
	@make fclean -C $(VISUAL)

re: fclean all
