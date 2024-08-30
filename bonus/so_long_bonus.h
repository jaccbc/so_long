/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:50:19 by joandre-          #+#    #+#             */
/*   Updated: 2024/08/27 12:26:41 by joandre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../lib/libft/libft.h"
# include "../lib/get_next_line/get_next_line.h"
# include "../lib/minilibx-linux/mlx.h"
# include <fcntl.h>
# include <X11/keysym.h>

# ifndef TILE_SIZE
#  define TILE_SIZE 50
# endif

typedef struct s_map
{
	bool	s;
	bool	c;
	size_t	e;
	size_t	p;
}	t_map;

typedef struct s_axis
{
	int	x;
	int	y;
}	t_axis;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	t_axis	px_size;
}	t_img;

typedef struct s_anim
{
	t_img	s0;
	t_img	s1;
	t_img	s2;
	t_img	s3;
	t_img	s4;
}	t_anim;

typedef struct s_game
{
	t_list	*map;
	t_img	p;
	t_anim	e;
	t_img	c;
	t_img	w;
	t_img	s;
	t_img	x;
	t_axis	player;
	int		moves;
}	t_game;

typedef struct s_mlx
{
	void	*init;
	void	*window;
	t_img	display;
	t_game	game;
}	t_mlx;

int		get_height(t_list *map);
char	get_asset(t_list *map, t_axis axi);
t_axis	get_axi(t_list *map, char asset);
t_list	*fetch_map(int fd);
t_list	*map_check(char *av);
bool	flood_fill(t_list *map);
void	build_map(t_mlx *libx);
void	print_error(char *msg);
void	close_program(char *err, int code, t_mlx libx);
void	game_event(t_axis next, t_mlx *libx);
void	hook_register(t_mlx *libx);

#endif
