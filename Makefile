# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joandre- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/05 17:45:46 by joandre-          #+#    #+#              #
#    Updated: 2024/08/21 19:46:59 by joandre-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
CLINK = -L./lib/ft_printf -lftprintf -L./lib/minilibx-linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
NAME = so_long
LIBFT = lib/ft_printf/libftprintf.a
GNL_D = lib/get_next_line
GNL = ${GNL_D}/get_next_line.c ${GNL_D}/get_next_line_utils.c
MLX = lib/minilibx-linux/libmlx_Linux.a
SRC = game_event.c build_map.c flood_fill.c map_utils.c map_check.c \
	  close_program.c hooks.c so_long.c
OBJ = $(SRC:.c=.o)
GNL_OBJ = $(GNL:.c=.o)


all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(CLINK) -o $(NAME)
$(MLX):
	make -s -C ./lib/minilibx-linux
$(LIBFT): $(GNL_OBJ)
	make bonus -s -C ./lib/ft_printf/libft
	make -s -C ./lib/ft_printf
	ar rcs $(LIBFT) $(GNL_OBJ)
	
clean:
	rm -rf $(OBJ) $(GNL_OBJ)
	make clean -s -C ./lib/ft_printf
	
fclean: clean
	rm -rf $(NAME)
	make fclean -s -C ./lib/ft_printf
	make clean -s -C ./lib/minilibx-linux

re: fclean all
