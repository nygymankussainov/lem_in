# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:51 by vhazelnu          #+#    #+#              #
#    Updated: 2019/11/11 15:38:47 by vhazelnu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LOG_NOCOLOR = \033[0m
LOG_GREEN = \033[32m

NAME = libftprintf.a

INCLUDES = -I ./ -I ../

LIBFT = ../

SRC = parse_char.c ft_printf.c ft_number.c parse_f.c parse_x.c parse_d.c parse_p.c parse_o.c parse_u.c width_for_float.c parse_b.c \
		longadd.c longmulti.c decimal_part.c longdiv.c integer_part.c rounding_and_print.c calculate_decimal.c width.c find_conv_or_whitesp.c \

SRCDIR = src
SRCS = $(addprefix $(SRCDIR)/, $(SRC))

OBJ = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
OBJDIR = obj

CCFL = -Wall -Wextra -Werror

.PHONY: all clean fclean re obj_dir library

all: obj_dir library $(NAME)

obj_dir:
	@mkdir -p $(OBJDIR)

library:
	@make -sC $(LIBFT)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@echo "$(LOG_GREEN)Ft_printf has compiled successfully!$(LOG_NOCOLOR)"
	@ranlib $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@gcc $(CCFL) -o $@ -c $< $(INCLUDES)
clean:
	@make clean -C $(LIBFT)
	@/bin/rm -rf $(OBJDIR)

fclean: clean
	@make fclean -C $(LIBFT)
	@/bin/rm -f $(NAME)

re: fclean all
