/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_program_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:40:15 by joandre-          #+#    #+#             */
/*   Updated: 2024/08/24 11:14:47 by joandre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	print_error(char *msg)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

static void	destroy_assets(t_mlx libx)
{
	mlx_destroy_image(libx.init, libx.game.p.img);
	mlx_destroy_image(libx.init, libx.game.e.s0.img);
	mlx_destroy_image(libx.init, libx.game.e.s1.img);
	mlx_destroy_image(libx.init, libx.game.e.s2.img);
	mlx_destroy_image(libx.init, libx.game.e.s3.img);
	mlx_destroy_image(libx.init, libx.game.e.s4.img);
	mlx_destroy_image(libx.init, libx.game.c.img);
	mlx_destroy_image(libx.init, libx.game.w.img);
	mlx_destroy_image(libx.init, libx.game.s.img);
	mlx_destroy_image(libx.init, libx.game.x.img);
}

void	close_program(char *err_msg, int code, t_mlx libx)
{
	ft_lstclear(&libx.game.map, free);
	if (code >= 3)
	{
		destroy_assets(libx);
		mlx_destroy_image(libx.init, libx.display.img);
	}
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
