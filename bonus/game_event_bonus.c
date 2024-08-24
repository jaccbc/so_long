/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_event_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:01:40 by joandre-          #+#    #+#             */
/*   Updated: 2024/08/24 13:20:45 by joandre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	put_string(t_mlx *libx, int moves)
{
	char	*count;
	char	asset;

	asset = get_asset(libx->game.map, (t_axis){0, 0});
	if (asset == '1')
		mlx_put_image_to_window(libx->init,
			libx->window, libx->game.w.img, 0, 0);
	else if (asset == '0')
		mlx_put_image_to_window(libx->init, libx->window,
			libx->game.s.img, 0, 0);
	count = ft_itoa(moves);
	mlx_string_put(libx->init, libx->window,
		TILE_SIZE / 3, TILE_SIZE / 2, 0xffffff, count);
	free(count);
}

static void	get_collectible(t_axis next, t_mlx *libx)
{
	t_axis	axi;
	t_list	*map;

	map = libx->game.map;
	while (map && next.y--)
		map = map->next;
	((char *)map->content)[next.x] = '0';
	axi = get_axi(libx->game.map, 'C');
	if (!axi.x && !axi.y)
	{
		axi = get_axi(libx->game.map, 'E');
		mlx_put_image_to_window(libx->init, libx->window,
			libx->game.e.s3.img, axi.x * TILE_SIZE, axi.y * TILE_SIZE);
		mlx_put_image_to_window(libx->init, libx->window,
			libx->game.e.s4.img, axi.x * TILE_SIZE, axi.y * TILE_SIZE);
	}
}

static void	trigger_event(t_mlx *libx, char asset, t_axis next)
{
	if (asset == 'C')
		get_collectible(next, libx);
	else if (asset == 'X')
	{
		ft_putendl_fd("[GAME OVER]", STDOUT_FILENO);
		close_program(NULL, 4, *libx);
	}
	if (asset == 'E')
	{
		ft_putendl_fd("[YOU WIN]", STDOUT_FILENO);
		close_program(NULL, 4, *libx);
	}
	mlx_put_image_to_window(libx->init, libx->window, libx->game.s.img,
		libx->game.player.x * TILE_SIZE, libx->game.player.y * TILE_SIZE);
	mlx_put_image_to_window(libx->init, libx->window, libx->game.p.img,
		next.x * TILE_SIZE, next.y * TILE_SIZE);
	libx->game.player = next;
	put_string(libx, ++libx->game.moves);
}

void	game_event(t_axis next, t_mlx *libx)
{
	t_axis		axi;
	char		asset;
	static int	i = 0;

	asset = get_asset(libx->game.map, next);
	axi = get_axi(libx->game.map, 'C');
	if (asset == '1' || (asset == 'E' && (axi.x && axi.y)))
		return ;
	if (axi.x && axi.y)
	{
		axi = get_axi(libx->game.map, 'E');
		if (i++ % 3)
			mlx_put_image_to_window(libx->init, libx->window,
				libx->game.e.s2.img, axi.x * TILE_SIZE, axi.y * TILE_SIZE);
		else if (i % 2)
			mlx_put_image_to_window(libx->init, libx->window,
				libx->game.e.s1.img, axi.x * TILE_SIZE, axi.y * TILE_SIZE);
		else
			mlx_put_image_to_window(libx->init, libx->window,
				libx->game.e.s0.img, axi.x * TILE_SIZE, axi.y * TILE_SIZE);
	}
	trigger_event(libx, asset, next);
}
