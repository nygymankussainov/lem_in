# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:51 by vhazelnu          #+#    #+#              #
#    Updated: 2019/08/27 17:04:02 by hfrankly         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = vizualizer

SDL = -I includes -L lib -l SDL2-2.0.0

INCLUDES = -L../libft -lft -I../libft -I./includes -I../

SRCS = srcs/main.c srcs/bresenham.c srcs/coords.c srcs/draw.c srcs/putants.c srcs/vizualizer.c \
srcs/vizualizer1.c srcs/sdl.c

all: $(NAME)

$(NAME):
	make -C ../libft/
	cc -g $(SRCS) $(SDL) $(INCLUDES) -o $(NAME)

clean:
	# make -C libft clean
	/bin/rm -rf $(OBJ)

fclean: clean
	# make -C libft fclean
	/bin/rm -rf $(NAME)
	/bin/rm -rf $(OBJDIR)

re: fclean all
