# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: relamine <relamine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 17:08:07 by saharchi          #+#    #+#              #
#    Updated: 2024/12/27 02:08:51 by relamine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D

LIBFT = ./libft/libft.a

CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -Ofast -g -fsanitize=address
RM = rm -f

SRC = main.c get_next_line.c get_next_line_utils.c my_split.c parsing_color.c parsing_map.c  parsing_texture.c parsing_utils.c parsing_utils_2.c \
		minimap.c map.c player_move.c raycasting.c

OBJ = $(SRC:%.c=%.o)
LIBMLX := ./MLX42
LIBS := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

all: $(NAME)

build:
	@cd MLX42 && cmake -B build && cmake --build build -j4 
	
$(LIBFT): ./libft/*.c ./libft/libft.h 
	make -C ./libft/

$(NAME): $(OBJ) $(LIBFT)
	cc $(CFLAGS)   $(OBJ) $(LIBFT) $(LIBS)  -o $(NAME)

%.o: %.c  
	cc $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	make -C ./libft/ clean

fclean: clean
	$(RM) $(NAME)
	make -C ./libft/ fclean

re: fclean all
