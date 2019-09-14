# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:51 by vhazelnu          #+#    #+#              #
#    Updated: 2019/09/14 16:40:45 by vhazelnu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ARCHIVE = vizualizer.a

NAME = visual

SDL = -L ~/.brew/Cellar/sdl2/2.0.10/lib -l SDL2-2.0.0 \
		`sdl2-config --libs` -lSDL2_gfx -lSDL2_mixer -lSDL2_ttf -lm

LIB = ../libft/ft_printf
LIB_A = ../libft/libft.a $(LIB)/libftprintf.a 

INCLUDES = -I../libft -I./includes -I./includes/SDL2 -I./includes/SDL2_GFX -I./includes/SDL2_MIX `sdl2-config --cflags`

SRCS = ../validation/work_with_data.c ../hash_func.c ../validation/validate_coords.c ../validation/find_and_connect_rooms.c \
		../validation/isint.c ../validation/validation.c ../validation/validate_rooms.c ../validation/write_data_in_sroom.c ../validation/validate_links.c ../validation/validate_ants.c \
		srcs/main.c srcs/coords.c srcs/draw.c srcs/putants.c srcs/vizualizer.c srcs/vizualizer1.c srcs/sdl.c srcs/coords1.c

OBJ = $(SRCS:.c=.o)

CCFL = -Wall -Wextra -Werror

all: $(ARCHIVE) $(NAME)

$(ARCHIVE): $(OBJ)
	@make -C $(LIB)
	@ar rc $(ARCHIVE) $(OBJ)
	@ranlib $(ARCHIVE)

%.o: %.c $(INCLUDES)
	@gcc -Wall -Wextra -Werror -c $<

$(NAME): $(OBJ)
	@gcc $(CCFL) -o ../$(NAME) $(SDL) $(ARCHIVE) $(LIB_A)

clean:
	@make clean -C $(LIB)
	@rm -f $(ARCHIVE)
	@rm -f ../$(NAME)
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LIB)

re: fclean all
