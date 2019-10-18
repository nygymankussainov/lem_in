# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:51 by vhazelnu          #+#    #+#              #
#    Updated: 2019/10/18 12:45:43 by vhazelnu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = visual

SDL = -L ~/.brew/Cellar/sdl2/2.0.10/lib -l SDL2-2.0.0 \
		`sdl2-config --libs` -lSDL2_gfx -lSDL2_mixer -lSDL2_ttf -lm

LIB = ../libft/ft_printf
LIB_A = ../libft/libft.a $(LIB)/libftprintf.a ../libftlemin.a

INCLUDES = -I../libft/ft_printf -I./includes -I./includes/SDL2 -I./includes/SDL2_GFX -I./includes/SDL2_MIX `sdl2-config --cflags`

SRCDIR = srcs

SRC = get_ants.c main.c coords.c draw.c putants.c vizualizer.c sdl.c coords1.c

SRCS = $(addprefix $(SRCDIR)/, $(SRC))

OBJ = $(SRC:.c=.o)

CCFL = -Wall -Wextra -Werror

all: $(NAME)

%.o: $(SRCDIR)/%.c
	@gcc -Wall -Wextra -Werror $(INCLUDES) -c $<

$(NAME): $(OBJ)
	@gcc $(CCFL) -o ../$(NAME) $(INCLUDES) $(SDL) $(SRCS) $(LIB_A)

clean:
	@make clean -C $(LIB)
	@rm -f $(ARCHIVE)
	@rm -f ../$(NAME)
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LIB)

re: fclean all
