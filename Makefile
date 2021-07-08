
_GREY=$ \033[30m
_RED=$ \033[31m
_GREEN=$ \033[32m
_YELLOW=$ \033[33m
_BLUE=$ \033[34m
_PURPLE=$ \033[35m
_CYAN=$ \033[36m
_WHITE=$ \033[37m
_END=$ \033[0m

NAME = fdf

SRC = srcs/fdf.c srcs/map.c srcs/events.c srcs/draw.c srcs/user_interface.c srcs/points.c

OBJ = fdf.o map.o events.o draw.o user_interface.o points.o

CFLAGS = -Werror -Wall -Wextra

MINILIB = ./minilibx-linux/libmlx.a

LIBFT = ./libft/libft.a

.SILENT:

all: $(NAME)

$(LIBFT):
	make -C ./libft

$(MINILIB):
	printf "\33[2K\r$(_CYAN)compiling: minilibx$(_END)"
	make -sC ./minilibx-linux > /dev/null 2>&1
	printf "\33[2K\r$(_GREEN)created: libmlx.a$(_END)\n"

$(NAME): $(MINILIB) $(LIBFT) $(SRC) srcs/fdf.h
	printf "\33[2K\r$(_YELLOW)building - $(_GREEN)$(NAME)$(_END)"
	clang $(CFLAGS) $(SRC) $(LIBFT) -lm -lXext -lX11 -lbsd $(MINILIB) -o $(NAME)
	printf "$(_GREEN)\nDone.$(_END)\n"

clean:
	make -sC ./minilibx-linux clean > /dev/null 2>&1
	printf "\33[2K\r$(_RED)deleted: minilibx$(_END)\n"
	make -sC ./libft clean

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(MINILIB)
	/bin/rm -f $(LIBFT)

re: fclean all
