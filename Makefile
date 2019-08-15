# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:51 by vhazelnu          #+#    #+#              #
#    Updated: 2019/08/15 19:55:27 by vhazelnu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ARCHIVE = lem_in.a

NAME = lem_in

LIB = libft/ft_printf
LIB_A = libft/libft.a $(LIB)/libftprintf.a

INCLUDES = -I ./libft -I ./libft/ft_printf/ -I ./includes

SRC = isint.c lem_in.c validation.c

OBJ = $(SRC:.c=.o)

CCFL = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(ARCHIVE) $(NAME)

$(ARCHIVE): $(OBJ)
	@make -C $(LIB)
	@ar rc $(ARCHIVE) $(OBJ)
	@ranlib $(ARCHIVE)

%.o: %.c $(INCLUDES)
	@gcc $(CCFL) -c $<

$(NAME): $(OBJ)
	@gcc $(CCFL) -o $(NAME) $(ARCHIVE) $(LIB_A) -g


clean:
	@make clean -C $(LIB)
	@rm -f $(ARCHIVE)
	@rm -f $(NAME)
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LIB)

re: fclean all
