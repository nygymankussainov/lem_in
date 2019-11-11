# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:51 by vhazelnu          #+#    #+#              #
#    Updated: 2019/11/11 15:42:03 by vhazelnu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visual

SDL = -L ~/.brew/Cellar/sdl2/2.0.10/lib -l SDL2-2.0.0 \
		`sdl2-config --libs` -lSDL2_gfx -lSDL2_mixer -lSDL2_ttf -lm

LIB = ../libft/ft_printf
LIB_A = ../libft/libft.a $(LIB)/libftprintf.a ../libftlemin.a

INCLUDES = -I../libft/ft_printf -I ../libft/ -I./includes -I./includes/SDL2 -I./includes/SDL2_GFX -I./includes/SDL2_MIX `sdl2-config --cflags`

SRCDIR = srcs
OBJDIR = obj

SRC = get_ants.c main.c coords.c draw.c putants.c vizualizer.c sdl.c coords1.c

SRCS = $(addprefix $(SRCDIR)/, $(SRC))

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

CCFL = -Wall -Wextra -Werror

.PHONY: all clean fclean re library viz obj_dir

all: obj_dir $(NAME)

obj_dir:
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@gcc $(CCFL) -o $@ -c $< $(INCLUDES)

$(NAME): $(OBJ)
	@gcc $(CCFL) -o ../$(NAME) $(INCLUDES) $(SDL) $(SRCS) $(LIB_A)

clean:
	@make clean -C $(LIB)
	@/bin/rm -f $(ARCHIVE)
	@/bin/rm -rf $(OBJDIR)

fclean: clean
	@/bin/rm -f ../$(NAME)

re: fclean all
