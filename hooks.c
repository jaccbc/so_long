/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:38:09 by joandre-          #+#    #+#             */
/*   Updated: 2024/08/20 21:06:52 by joandre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	key_close(int keysym, t_mlx *libx)
{
	if (keysym == XK_Escape)
		close_program(NULL, 4, *libx);
	return (0);
}

static int	game_key(int keysym, t_mlx *libx)
{
	t_axis	next;

	next = libx->game.player;
	if (keysym == XK_w || keysym == XK_Up)
		--next.y;
	else if (keysym == XK_s || keysym == XK_Down)
		++next.y;
	else if (keysym == XK_a || keysym == XK_Left)
		--next.x;
	else if (keysym == XK_d || keysym == XK_Right)
		++next.x;
	else
		return (1);
	game_event(next, libx);
	return (0);
}

static int	mouse_close(t_mlx *libx)
{
	return (close_program(NULL, 4, *libx), 0);
}

void	hook_register(t_mlx *libx)
{
	mlx_hook(libx->window, 3, 1L << 1, key_close, libx);
	mlx_hook(libx->window, 17, 1L << 17, mouse_close, libx);
	mlx_hook(libx->window, 2, 1L << 0, game_key, libx);
}
