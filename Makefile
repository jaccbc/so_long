# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joandre- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/05 17:45:46 by joandre-          #+#    #+#              #
#    Updated: 2024/08/24 13:13:49 by joandre-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
CLINK = -L./lib/libft -lft -L./lib/minilibx-linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
NAME = so_long
BONUS = so_long_bonus
LIBFT = lib/libft/libft.a
MLX = lib/minilibx-linux/libmlx_Linux.a
GNL_D = lib/get_next_line
GNL = ${GNL_D}/get_next_line.c ${GNL_D}/get_next_line_utils.c
SRC = game_event.c build_map.c flood_fill.c map_utils.c map_check.c \
	  close_program.c hooks.c so_long.c
BONUS_SRC = bonus/game_event_bonus.c bonus/build_map_bonus.c \
			bonus/flood_fill_bonus.c bonus/map_utils_bonus.c \
			bonus/map_check_bonus.c bonus/close_program_bonus.c \
			bonus/hooks_bonus.c bonus/so_long_bonus.c
OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)
GNL_OBJ = $(GNL:.c=.o)


all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(CLINK) -o $(NAME)
$(MLX):
	make -s -C ./lib/minilibx-linux
$(LIBFT): $(GNL_OBJ)
	make bonus -s -C ./lib/libft
	ar rcs $(LIBFT) $(GNL_OBJ)

bonus: $(BONUS)
$(BONUS): $(MLX) $(LIBFT) $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(CLINK) -o $(BONUS)

clean:
	rm -rf $(OBJ) $(GNL_OBJ) $(BONUS_OBJ)
	make clean -s -C ./lib/libft
	
fclean: clean
	rm -rf $(NAME) $(BONUS)
	make fclean -s -C ./lib/libft
	make clean -s -C ./lib/minilibx-linux

re: fclean all
