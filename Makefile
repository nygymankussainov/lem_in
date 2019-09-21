# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:51 by vhazelnu          #+#    #+#              #
#    Updated: 2019/09/20 13:41:40 by hfrankly         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ARCHIVE = lem-in.a

NAME = lem-in

LIB = libft/ft_printf
LIB_A = libft/libft.a $(LIB)/libftprintf.a 

INCLUDES = -I ./libft -I ./libft/ft_printf/ -I .

W/P = algorithm/work_with_pathes
SA = algorithm/send_ants
RF = algorithm/refresh

SRC = lem_in.c hash_func.c validation/validate_coords.c validation/find_and_connect_rooms.c bfs.c find_shortest_path.c \
		validation/isint.c validation/validation.c validation/validate_rooms.c validation/write_data_in_sroom.c validation/validate_links.c validation/validate_ants.c \
		helpful_func.c validation/work_with_data.c algorithm/algo.c $(W/P)/reverse_path.c $(W/P)/make_duplicate_room.c \
		$(W/P)/create_links.c $(W/P)/init_duplicates.c $(SA)/send_ants.c $(SA)/pickout_pathes.c $(RF)/refresh_graph.c \
		$(RF)/rooms_management.c

OBJ = $(SRC:.c=.o)

CCFL = -Wall -Wextra -Werror

all: $(NAME)

$(ARCHIVE): $(OBJ)
	@make -C $(LIB)
	@ar rc $(ARCHIVE) $(OBJ)
	@ranlib $(ARCHIVE)

%.o: %.c
	@gcc $(INCLUDES) -Wall -Wextra -Werror -c $<

$(NAME): 
	@make -C $(LIB)
	@gcc -Wall -Wextra -Werror $(INCLUDES) -o $(NAME) $(SRC) $(LIB_A) $(SDL) -g

clean:
	@make clean -C $(LIB)
	@rm -f $(ARCHIVE)
	@rm -f $(NAME)
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LIB)

re: fclean all

.PHONY: all clean fclean re
