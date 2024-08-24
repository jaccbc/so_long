/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 02:41:42 by joandre-          #+#    #+#             */
/*   Updated: 2024/08/21 22:58:04 by joandre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static bool	valid(char c, t_map *game)
{
	if (c == '0')
		game->s = true;
	else if (c == '1' || c == '\n')
		return (true);
	else if (c == 'C')
		game->c = true;
	else if (c == 'E')
		++game->e;
	else if (c == 'P')
		++game->p;
	else
		return (false);
	return (true);
}

static bool	valid_characters(t_list *map)
{
	size_t	i;
	t_map	asset;

	ft_bzero(&asset, sizeof(asset));
	while (map)
	{
		i = 0;
		while (valid((((char *)map->content)[i]), &asset))
			++i;
		if (((char *)map->content)[i] != '\0')
			break ;
		map = map->next;
	}
	if (asset.s && asset.c && asset.e == 1 && asset.p == 1)
		return (true);
	return (false);
}

static bool	last_row(char *row, size_t len)
{
	size_t	i;

	if (!row)
		return (false);
	i = ft_strlen(row);
	if (len == i && row[i - 1] == '\n')
		return (true);
	if (--len == i)
		return (true);
	return (false);
}

static bool	rectangle(t_list *map)
{
	t_axis	axi;

	axi.y = get_height(map);
	axi.x = ft_strlen(map->content);
	if (axi.y == axi.x - 1)
		return (false);
	while (map->next)
	{
		if (axi.x != (int)ft_strlen(map->content))
			break ;
		map = map->next;
	}
	if (map->next == NULL)
		if (last_row(map->content, axi.x))
			map = map->next;
	while (map)
	{
		if (((char *)map->content)[0] != '\n')
			break ;
		map = map->next;
	}
	if (map)
		return (false);
	return (true);
}

t_list	*map_check(char *av)
{
	char	*err;
	int		fd;
	t_list	*map;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (print_error("Unable to open the map file"), NULL);
	map = fetch_map(fd);
	if (map)
	{
		err = NULL;
		if (!valid_characters(map))
			err = "Only 5 characters allowed: 0 1 C E P";
		if (!rectangle(map) && !err)
			err = "The map must be rectangular";
		if (err)
			print_error(err);
		else if (!flood_fill(map))
			return (map);
		return (ft_lstclear(&map, free), NULL);
	}
	return (print_error("Unable to read the map file"), NULL);
}
