/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:22:36 by joandre-          #+#    #+#             */
/*   Updated: 2024/08/22 15:02:29 by joandre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static t_list	*argv_check(int ac, char **av)
{
	char	*name;

	if (ac != 2)
		return (print_error("./so_long <MAP FILE>"), NULL);
	name = ft_strrchr(av[1], '.');
	if (name)
	{
		if (!ft_strncmp(".ber", name, 4))
			return (map_check(av[1]));
	}
	print_error("The map file must end with the .ber extension");
	return (NULL);
}

static void	libx_init(t_mlx *libx)
{
	char	*err_msg;
	t_list	*map;

	err_msg = "MiniLibX failure!";
	map = libx->game.map;
	libx->display.px_size.y = (get_height(map) * TILE_SIZE);
	libx->display.px_size.x = ((ft_strlen(map->content) - 1) * TILE_SIZE);
	libx->init = mlx_init();
	if (!libx->init)
		close_program(err_msg, 0, *libx);
	libx->window = mlx_new_window(libx->init,
			libx->display.px_size.x, libx->display.px_size.y, "so_long");
	if (!libx->window)
		close_program(err_msg, 1, *libx);
	libx->display.img = mlx_new_image(libx->init,
			libx->display.px_size.x, libx->display.px_size.y);
	if (!libx->display.img)
		close_program(err_msg, 2, *libx);
	libx->display.addr = mlx_get_data_addr(libx->display.img,
			&libx->display.bpp, &libx->display.size_line,
			&libx->display.endian);
	if (!libx->display.addr)
		close_program(err_msg, 3, *libx);
}

int	main(int argc, char **argv)
{
	t_mlx	libx;

	ft_bzero(&libx, sizeof(libx));
	libx.game.map = argv_check(argc, argv);
	if (!libx.game.map)
		return (-1);
	libx_init(&libx);
	build_map(&libx);
	hook_register(&libx);
	mlx_loop(libx.init);
}
