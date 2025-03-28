# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: recherra <recherra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/05 17:42:36 by recherra          #+#    #+#              #
#    Updated: 2025/03/28 17:31:35 by recherra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FRAMEWORKS=-lmlx -framework OpenGL -framework AppKit
FLAGS=-Wall -Wextra -Werror -O3
GENERAL= parsing/get_map___.c parsing/check_map.c parsing/get_map__.c parsing/get_map_.c parsing/get_map.c parsing/cf_news__.c parsing/news_parsing.c parsing/cf_parsing__.c parsing/cf_parsing.c parsing/next_line.c \
		parsing/map.c arg_checker.c rotate.c player_position.c  mlx_setup.c print_objects.c mlx_rebuild.c error_miscs.c init_player_info.c \
		init_textures.c keys_hook.c hooks_utils.c render_wall.c celine_floor.c game.c mlx_utils.c ray_casting.c rays.c horizontal_inters.c vertical_inters.c \
		ray_casting_utils.c  hooks_utils_utils.c  bonus/collision_bonus.c 
SRC= ${GENERAL} cube.c  minimap.c re_render.c
SRC_BONUS= ${GENERAL} bonus/cube_bonus.c bonus/minimap_bonus.c bonus/mouse_hook_bonus.c bonus/re_render_bonus.c bonus/dda.c
OBJS=${SRC:.c=.o}
OBJS_BONUS=${SRC_BONUS:.c=.o}
LIBFT=libft/libft.a
NAME=cub3D
NAME_BONUS=cub3D_bonus

all: ${NAME}

${NAME}: ${LIBFT} ${OBJS}
	cc ${FLAGS} ${OBJS} -o ${NAME}  ${LIBFT} ${FRAMEWORKS}

bonus: ${NAME_BONUS}

${NAME_BONUS}: ${LIBFT} ${OBJS_BONUS}
	cc ${FLAGS} ${OBJS_BONUS} -o ${NAME_BONUS} ${LIBFT} ${FRAMEWORKS}

${LIBFT}:
	make -C libft/

%_bonus.o: %_bonus.c bonus/cube_bonus.h
	cc $(FLAGS) -c $< -o $@
	
%.o: %.c cube.h
	cc $(FLAGS) -c $< -o $@

clean:
	make -C libft/ clean
	rm -f	${OBJS}
	rm -f	${OBJS_BONUS} 

fclean: clean
	make -C libft/ fclean
	rm -f ${NAME}
	rm -f ${NAME_BONUS}

re: fclean all
