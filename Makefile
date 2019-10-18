# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:51 by vhazelnu          #+#    #+#              #
#    Updated: 2019/10/18 12:57:42 by vhazelnu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LOG_NOCOLOR = \033[0m
LOG_GREEN = \033[32m

ARCHIVE = libftlemin.a

NAME = lem-in

LIB = libft/ft_printf
LIB_A = libft/libft.a $(LIB)/libftprintf.a 
VISUAL = ./vizualizer

INCLUDES = -I ./ -I libft/ft_printf

SOURCES = lem_in.c hash_func.c bfs.c bellman_ford.c run_ants.c unvisit_rooms.c delete_dup_rooms.c \
		sort_paths.c create_new_arr_path.c create_paths.c create_dup_rooms.c push_ant.c print_graph.c lock_collided_links.c \
		manage_directions.c is_need_more_paths.c change_link_room.c count_optimal_paths.c \
		isint.c validation.c validate_rooms.c write_data_in_sroom.c validate_links.c validate_ants.c \
		work_with_data.c validate_coords.c find_and_connect_rooms.c \

SRCDIR = src

SRC = $(addprefix $(SRCDIR)/, $(SOURCES))

OBJ = $(patsubst %.c, %.o, $(SOURCES))

CCFL = -Wall -Wextra -Werror

.PHONY: all clean fclean re liba viz

all: liba $(ARCHIVE) $(NAME) viz

liba:
	@make -sC $(LIB)

%.o: $(SRCDIR)/%.c
	@gcc $(CCFL) -c $< $(INCLUDES)

$(ARCHIVE): $(OBJ)
	@ar rc $(ARCHIVE) $(OBJ)
	@ranlib $(ARCHIVE)

$(NAME): $(OBJ)
	@gcc $(CCFL) -o $(NAME) $(ARCHIVE) $(LIB_A)
	@echo "$(LOG_GREEN)Lem_in is compiled!$(LOG_NOCOLOR)"

viz:
	@make -sC $(VISUAL)
	@echo "$(LOG_GREEN)Visual is compiled!$(LOG_NOCOLOR)"

clean:
	@make clean -sC $(LIB)
	@make clean -sC $(VISUAL)
	@rm -r $(OBJ)

fclean: clean
	@rm -f $(ARCHIVE)
	@rm -f $(NAME)
	@make fclean -sC $(LIB)
	@make fclean -sC $(VISUAL)

re: fclean all
