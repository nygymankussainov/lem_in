# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:51 by vhazelnu          #+#    #+#              #
#    Updated: 2019/08/17 12:09:52 by vhazelnu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ARCHIVE = lem_in.a

NAME = lem_in

LIB = libft/ft_printf
LIB_A = libft/libft.a $(LIB)/libftprintf.a

INCLUDES = -I ./libft -I ./libft/ft_printf/ -I ./includes

SRC = lem_in.c \
		validation/isint.c validation/validation.c validation/validate_links.c validation/validate_rooms.c \

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

$(NAME): $(OBJ)
	@gcc -Wall -Wextra -Werror -o $(NAME) $(ARCHIVE) $(LIB_A) -g

clean:
	@make clean -C $(LIB)
	@rm -f $(ARCHIVE)
	@rm -f $(NAME)
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LIB)

re: fclean all
