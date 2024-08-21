/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:01:40 by joandre-          #+#    #+#             */
/*   Updated: 2024/08/21 17:08:59 by joandre-         ###   ########.fr       */
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

void	game_event(t_axis next, t_mlx *libx)
{
	char	asset;
	t_axis	result;

	asset = get_asset(libx->game.map, next);
	if (asset == '1')
		return ;
	if (asset == 'C')
		get_collectible(next, libx);
	else if (asset == 'E')
	{
		result = get_axi(libx->game.map, 'C');
		if (result.x && result.y)
			return ;
		ft_putendl_fd("\n[YOU WIN!]", STDOUT_FILENO);
		close_program(NULL, 4, *libx);
	}
	mlx_put_image_to_window(libx->init, libx->window, libx->game.s.img,
		libx->game.player.x * ASSET_SIZE, libx->game.player.y * ASSET_SIZE);
	mlx_put_image_to_window(libx->init, libx->window, libx->game.p.img,
		next.x * ASSET_SIZE, next.y * ASSET_SIZE);
	libx->game.player = next;
	ft_printf("[MOVES] %u\n", ++libx->game.moves);
}
