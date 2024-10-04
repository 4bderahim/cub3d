
NAME	:= three_dee
CFLAGS	:=  -Wunreachable-code -Ofast 
LIBMLX	:= ~/MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	:= cube.c map.c
OBJS	:= ${SRCS:.c=.o}
MLX_FLAGS    = ~/MLX42/build/libmlx42.a -Iinclude -lm -framework Cocoa -framework OpenGL -framework IOKit	
all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C  $(LIBMLX)/build -j4


$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(MLX_FLAGS) $(LIBS) $(HEADERS) -o $(NAME)
	
%.o: %.c so_long.h
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
fclean: clean
	@rm -rf $(NAME)
re: clean all