/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:24:16 by joandre-          #+#    #+#             */
/*   Updated: 2024/08/27 12:21:37 by joandre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	load_asset(t_mlx *libx, char *path, t_img *asset)
{
	asset->img = mlx_xpm_file_to_image(libx->init, path,
			&asset->px_size.x, &asset->px_size.y);
	if (!asset->img)
		close_program("Failure loading game asset", 4, *libx);
	asset->addr = mlx_get_data_addr(asset->img,
			&asset->bpp, &asset->size_line, &asset->endian);
	if (!asset->addr)
		close_program("Failure reading asset info", 4, *libx);
}

static void	load_game(t_mlx *libx)
{
	libx->game.player = get_axi(libx->game.map, 'P');
	load_asset(libx, "./assets/space.xpm", &libx->game.s);
	load_asset(libx, "./assets/wall.xpm", &libx->game.w);
	load_asset(libx, "./assets/player.xpm", &libx->game.p);
	load_asset(libx, "./assets/exit.xpm", &libx->game.e);
	load_asset(libx, "./assets/collectible.xpm", &libx->game.c);
}

static void	place_image(char asset, t_mlx *libx, t_axis axi)
{
	if (asset == '1')
		mlx_put_image_to_window(libx->init, libx->window,
			libx->game.w.img, axi.x * TILE_SIZE, axi.y * TILE_SIZE);
	else if (asset == '0')
		mlx_put_image_to_window(libx->init, libx->window,
			libx->game.s.img, axi.x * TILE_SIZE, axi.y * TILE_SIZE);
	else if (asset == 'C')
		mlx_put_image_to_window(libx->init, libx->window,
			libx->game.c.img, axi.x * TILE_SIZE, axi.y * TILE_SIZE);
	else if (asset == 'E')
		mlx_put_image_to_window(libx->init, libx->window,
			libx->game.e.img, axi.x * TILE_SIZE, axi.y * TILE_SIZE);
	else if (asset == 'P')
		mlx_put_image_to_window(libx->init, libx->window, libx->game.p.img,
			libx->game.player.x * TILE_SIZE,
			libx->game.player.y * TILE_SIZE);
}

void	build_map(t_mlx *libx)
{
	t_list	*map;
	t_axis	axi;
	t_axis	limit;

	map = libx->game.map;
	limit.y = get_height(libx->game.map);
	limit.x = (int)(ft_strlen(libx->game.map->content) - 1);
	load_game(libx);
	axi.y = 0;
	while (axi.y < limit.y)
	{
		axi.x = 0;
		while (axi.x < limit.x)
		{
			place_image(((char *)map->content)[axi.x], libx, axi);
			++axi.x;
		}
		map = map->next;
		++axi.y;
	}
}
