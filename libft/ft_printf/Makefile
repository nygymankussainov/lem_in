# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:51 by vhazelnu          #+#    #+#              #
#    Updated: 2019/10/17 15:06:26 by vhazelnu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

LIBFT = ../

SRCS = ft_symbol.c ft_printf.c ft_number.c ft_conv_f.c ft_conv_x.c ft_conv_d.c ft_conv_p.c ft_conv_o.c ft_conv_u.c width_for_f.c ft_conv_b.c \
		longadd.c longmulti.c decimal_part.c longdiv.c integer_part.c rounding_and_print.c calculate_decimal.c width.c find_conv_or_whitesp.c \

OBJS = $(SRCS:.c=.o)
OBJS2 = ft_atoi.o ft_atoi_base.o ft_bzero.o ft_isalpha.o ft_isdigit.o ft_itoa_base.o \
		ft_itoa_ll.o ft_memalloc.o ft_memcpy.o ft_memset.o ft_power.o ft_putchar.o ft_putstr.o ft_realloc.o \
		ft_revstr.o ft_strchr.o ft_strcmp.o ft_strcpy.o ft_strdup.o ft_strjoin.o ft_strlen.o ft_strncpy.o \
		ft_strndup.o ft_strnew.o ft_swap.o ft_swap_str.o ft_uitoa_base.o iswhitesp.o ft_bzero_null.o \
		ft_islower.o ft_isupper.o ft_memdel.o ft_skip_whitesp.o ft_strcat.o
OBJS_LIB = $(addprefix $(LIBFT), $(OBJS2))

CCFL = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@make -sC $(LIBFT)
	@ar rc $(NAME) $(OBJS) $(OBJS_LIB)
	@echo ft_printf is compiled!
	@ranlib $(NAME)

%.o: %.c
	@gcc $(CCFL) -c $<

clean:
	@make clean -C $(LIBFT)
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT)
	@rm -f $(NAME)

re: fclean all
