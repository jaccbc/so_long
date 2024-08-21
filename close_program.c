/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:12:24 by joandre-          #+#    #+#             */
/*   Updated: 2024/08/21 16:39:39 by joandre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_error(char *msg)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

static void	destroy_assets(t_mlx libx)
{
	mlx_destroy_image(libx.init, libx.game.p.img);
	mlx_destroy_image(libx.init, libx.game.e.img);
	mlx_destroy_image(libx.init, libx.game.c.img);
	mlx_destroy_image(libx.init, libx.game.w.img);
	mlx_destroy_image(libx.init, libx.game.s.img);
}

void	close_program(char *err_msg, int code, t_mlx libx)
{
	ft_lstclear(&libx.game.map, free);
	if (code > 3)
		destroy_assets(libx);
	if (code >= 3)
		mlx_destroy_image(libx.init, libx.display.img);
	if (code >= 2)
		mlx_destroy_window(libx.init, libx.window);
	mlx_destroy_display(libx.init);
	free(libx.init);
	if (err_msg)
	{
		print_error(err_msg);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
