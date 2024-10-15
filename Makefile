# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: recherra <recherra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/05 17:42:36 by recherra          #+#    #+#              #
#    Updated: 2024/10/05 17:42:48 by recherra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# FRAMEWORKS=-L/Users/ael-krid/minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit
FRAMEWORKS=-lmlx -framework OpenGL -framework AppKit
FLAGS=-Wall -Wextra -fsanitize=address -g
# FLAGS=-Wall -Wextra 
SRC=map.c cube.c hooks.c rotate.c mlx_setup.c print_objects.c minimap.c mlx_rebuild.c factors.c error_miscs.c init_player_info.c
OBJS=${SRC:.c=.o}
LIBFT=libft/libft.a
NAME=three_dee

all: ${NAME}

${NAME}: ${LIBFT} ${OBJS}
	cc ${OBJS} -o ${NAME} ${FLAGS} ${LIBFT} ${FRAMEWORKS}

${LIBFT}:
	make -C libft/

${OBJS}: cubed.h

clean:
	make -C libft/ clean
	rm -rf ${OBJS}

fclean: clean
	make -C libft/ fclean
	rm ${NAME}

re: fclean all
