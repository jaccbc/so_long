/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:01:40 by joandre-          #+#    #+#             */
/*   Updated: 2024/08/24 13:04:19 by joandre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	get_collectible(t_axis next, t_mlx *libx)
{
	t_list	*map;

	map = libx->game.map;
	while (map && next.y--)
		map = map->next;
	((char *)map->content)[next.x] = '0';
}

static void	trigger_event(t_axis next, t_mlx *libx)
{
	char	*moves;

	mlx_put_image_to_window(libx->init, libx->window, libx->game.s.img,
		libx->game.player.x * TILE_SIZE, libx->game.player.y * TILE_SIZE);
	mlx_put_image_to_window(libx->init, libx->window, libx->game.p.img,
		next.x * TILE_SIZE, next.y * TILE_SIZE);
	libx->game.player = next;
	moves = ft_itoa(++libx->game.moves);
	if (!moves)
		close_program("Failed to print player movement counter", 4, *libx);
	ft_putendl_fd(moves, STDOUT_FILENO);
	free(moves);
}

void	game_event(t_axis next, t_mlx *libx)
{
	char	asset;
	t_axis	axi;

	asset = get_asset(libx->game.map, next);
	if (asset == '1')
		return ;
	if (asset == 'C')
		get_collectible(next, libx);
	else if (asset == 'E')
	{
		axi = get_axi(libx->game.map, 'C');
		if (axi.x && axi.y)
			return ;
		ft_putendl_fd("[YOU WIN]", STDOUT_FILENO);
		close_program(NULL, 4, *libx);
	}
	trigger_event(next, libx);
}
