# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:51 by vhazelnu          #+#    #+#              #
#    Updated: 2019/10/22 14:30:42 by vhazelnu         ###   ########.fr        #
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
		sort_paths.c create_new_arr_path.c create_paths.c create_dup_rooms.c push_ant.c print_path.c \
		manage_directions.c change_link_room.c count_optimal_paths.c create_linkwith_list.c \
		isint.c validation.c validate_rooms.c write_data_in_sroom.c validate_links.c validate_ants.c \
		work_with_data.c validate_coords.c find_and_connect_rooms.c \

SRCDIR = src
OBJDIR = obj

SRC = $(addprefix $(SRCDIR)/, $(SOURCES))

OBJ = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

CCFL = -Wall -Wextra -Werror

.PHONY: all clean fclean re library viz obj_dir

all: obj_dir library $(ARCHIVE) $(NAME) viz

obj_dir:
	@mkdir -p $(OBJDIR)

library:
	@make -sC $(LIB)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@gcc $(CCFL) -o $@ -c $< $(INCLUDES)

$(ARCHIVE): $(OBJ)
	@ar rc $(ARCHIVE) $(OBJ)
	@ranlib $(ARCHIVE)

$(NAME): $(OBJ)
	@gcc $(CCFL) -o $(NAME) $(ARCHIVE) $(LIB_A)
	@echo "$(LOG_GREEN)Lem_in has compiled successfully!$(LOG_NOCOLOR)"

viz:
	@make -sC $(VISUAL)
	@echo "$(LOG_GREEN)Visual has compiled successfully!$(LOG_NOCOLOR)"

clean:
	@make clean -sC $(LIB)
	@make clean -sC $(VISUAL)
	@/bin/rm -rf $(OBJDIR)

fclean: clean
	@/bin/rm -f $(ARCHIVE)
	@/bin/rm -f $(NAME)
	@make fclean -sC $(LIB)
	@make fclean -sC $(VISUAL)

re: fclean all
