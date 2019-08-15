# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/20 19:05:15 by hfrankly          #+#    #+#              #
#    Updated: 2019/08/15 16:16:22 by hfrankly         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in

FLAGS = -Wall -Wextra -Werror -g

MLX = -I /usr/local/include -L /usr/local/include -lmlx -framework OpenGL -framework Appkit

INCLUDES = -L./libft -lft -I ./libft -I./includes

SRCS = srcs/main.c

OBJ = $(addprefix $(OBJDIR)/, $(patsubst $(SRCSDIR)/%.c, %.o, $(wildcard $(SRCSDIR)/*.c)))

SRCSDIR = srcs

OBJDIR = objdir

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCSDIR)/%.c $(INCLUDES)
	cc $(FLAGS) -I . -o $@ -c $<

$(NAME): $(OBJ)
	make -C libft/
	cc $(FLAGS) $(MLX) $(OBJ) -o $(NAME)

clean:
	make -C libft clean
	/bin/rm -rf $(OBJ)

fclean: clean
	make -C libft fclean
	/bin/rm -rf $(NAME)
	/bin/rm -rf $(OBJDIR)

re: fclean all

.PHONY: all clean fclean re
