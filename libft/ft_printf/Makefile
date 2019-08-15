# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:51 by vhazelnu          #+#    #+#              #
#    Updated: 2019/08/06 13:32:41 by vhazelnu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

LIB = -L ../ -lft

INCLUDES = -I ./includes -I ../includes

SRCS = ft_symbol.c ft_printf.c ft_number.c ft_conv_f.c ft_conv_x.c ft_conv_d.c ft_conv_p.c ft_conv_o.c ft_conv_u.c width_for_f.c ft_conv_b.c \
		longadd.c longmulti.c decimal_part.c longdiv.c integer_part.c rounding_and_print.c calculate_decimal.c width.c find_conv_or_whitesp.c \
		../ft_atoi.c ../ft_atoi_base.c ../ft_bzero.c ../ft_isalpha.c ../ft_isdigit.c ../ft_itoa_base.c \
		../ft_itoa_ll.c ../ft_memalloc.c ../ft_memcpy.c ../ft_memset.c ../ft_power.c ../ft_putchar.c ../ft_putstr.c ../ft_realloc.c \
		../ft_revstr.c ../ft_strchr.c ../ft_strcmp.c ../ft_strcpy.c ../ft_strdup.c ../ft_strjoin.c ../ft_strlen.c ../ft_strncpy.c \
		../ft_strndup.c ../ft_strnew.c ../ft_swap.c ../ft_swap_str.c ../ft_uitoa_base.c ../iswhitesp.c ../ft_bzero_null.c \
		../ft_islower.c ../ft_isupper.c ../ft_memdel.c ../ft_skip_whitesp.c ../ft_strcat.c

OBJS = $(SRCS:.c=.o) ../ft_atoi.o ../ft_atoi_base.o ../ft_bzero.o ../ft_isalpha.o ../ft_isdigit.o ../ft_itoa_base.o \
		../ft_itoa_ll.o ../ft_memalloc.o ../ft_memcpy.o ../ft_memset.o ../ft_power.o ../ft_putchar.o ../ft_putstr.o ../ft_realloc.o \
		../ft_revstr.o ../ft_strchr.o ../ft_strcmp.o ../ft_strcpy.o ../ft_strdup.o ../ft_strjoin.o ../ft_strlen.o ../ft_strncpy.o \
		../ft_strndup.o ../ft_strnew.o ../ft_swap.o ../ft_swap_str.o ../ft_uitoa_base.o ../iswhitesp.o ../ft_bzero_null.o \
		../ft_islower.o ../ft_isupper.o ../ft_memdel.o ../ft_skip_whitesp.o ../ft_strcat.o

CCFL = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ../
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

%.o: %.c $(INCLUDES)
	@gcc $(CCFL) -c $(SRCS) $(LIB)

clean:
	@make clean -C ../
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C ../
	@rm -f $(NAME)

re: fclean all
	@make re -C ../
