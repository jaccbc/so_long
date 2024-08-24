/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:10:06 by joandre-          #+#    #+#             */
/*   Updated: 2024/08/21 22:32:23 by joandre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	get_height(t_list *map)
{
	int	i;

	i = 0;
	while (map)
	{
		if (((char *)map->content)[0] == '\n')
			break ;
		map = map->next;
		++i;
	}
	return (i);
}

char	get_asset(t_list *map, t_axis axi)
{
	if (!map)
		return (0);
	if (axi.y >= get_height(map) || axi.x >= (int)ft_strlen(map->content) - 1)
		return (0);
	while (map && axi.y--)
		map = map->next;
	return (((char *)map->content)[axi.x]);
}

t_axis	get_axi(t_list *map, char asset)
{
	t_axis	axi;

	axi.y = 0;
	while (map)
	{
		axi.x = 0;
		while (((char *)map->content)[axi.x]
			&& ((char *)map->content)[axi.x] != asset)
			++axi.x;
		if (((char *)map->content)[axi.x] == asset)
			break ;
		map = map->next;
		++axi.y;
	}
	if (map)
		if (((char *)map->content)[axi.x])
			return (axi);
	return (ft_bzero(&axi, sizeof(axi)), axi);
}

t_list	*fetch_map(int fd)
{
	char	*line;
	t_list	*row;
	t_list	*map;

	map = NULL;
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		row = ft_lstnew(line);
		if (!row)
		{
			ft_lstclear(&map, free);
			break ;
		}
		ft_lstadd_back(&map, row);
	}
	close(fd);
	if (!map)
		return (print_error("Memory allocation failure!"), NULL);
	return (map);
}
