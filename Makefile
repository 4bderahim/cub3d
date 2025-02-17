# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: recherra <recherra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/05 17:42:36 by recherra          #+#    #+#              #
#    Updated: 2025/02/17 21:13:15 by recherra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# FRAMEWORKS=-lmlx_Linux -lXext -lX11 -lm -lz
FRAMEWORKS=-lmlx -framework OpenGL -framework AppKit
FLAGS=-Wall -Wextra -Werror
SRC= 	parsing/get_map___.c parsing/get_map__.c parsing/get_map.c parsing/news_parsing.c parsing/cf_parsing.c parsing/next_line.c \
		parsing/map.c cube.c hooks.c rotate.c mlx_setup.c print_objects.c minimap.c mlx_rebuild.c factors.c error_miscs.c init_player_info.c \
		init_textures.c hooks_utils.c ray_dda.c render_wall.c celine_floor.c game.c mlx_utils.c ray_casting.c rays.c
OBJS=${SRC:.c=.o}
LIBFT=libft/libft.a
NAME=cub3D

all: ${NAME}

${NAME}: ${LIBFT} ${OBJS}
	gcc ${FLAGS} ${OBJS} -o ${NAME}  ${LIBFT} ${FRAMEWORKS}

${LIBFT}:
	make -C libft/

%.o: %.c cubed.h
	gcc $(FLAGS) -c $< -o $@

clean:
	make -C libft/ clean
	rm -rf ${OBJS}

fclean: clean
	make -C libft/ fclean
	rm ${NAME}

re: fclean all
