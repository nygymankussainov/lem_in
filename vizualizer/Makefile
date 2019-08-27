# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:51 by vhazelnu          #+#    #+#              #
#    Updated: 2019/08/27 16:17:37 by vhazelnu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SDL = -I includes -L lib -l SDL2-2.0.0

INCLUDES = -L./libft -lft -I ./libft -I./includes -I./gnl

SRCS = srcs/main.c srcs/bresenham.c srcs/coords.c srcs/draw.c srcs/putants.c srcs/vizualizer.c \
srcs/vizualizer1.c srcs/sdl.c gnl/get_next_line.c

OBJ = $(SRC:.c=.o)

CCFL = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(ARCHIVE) $(NAME)

$(ARCHIVE): $(OBJ)
	@make -C $(LIB)
	@ar rc $(ARCHIVE) $(OBJ)
	@ranlib $(ARCHIVE)

%.o: %.c $(INCLUDES)
	@gcc -Wall -Wextra -Werror -c $<

$(NAME):
	make -C libft/
	cc -g $(SRCS) $(MLX) $(SDL) $(INCLUDES) -o $(NAME)

clean:
	# make -C libft clean
	/bin/rm -rf $(OBJ)

fclean: clean
	# make -C libft fclean
	/bin/rm -rf $(NAME)
	/bin/rm -rf $(OBJDIR)

re: fclean all
