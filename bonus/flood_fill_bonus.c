/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:10:06 by joandre-          #+#    #+#             */
/*   Updated: 2024/08/24 13:46:29 by joandre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static t_axis	find_asset(char **map, int map_y, char asset)
{
	t_axis	axi;

	axi.y = 0;
	while (axi.y < map_y)
	{
		axi.x = 0;
		while (map[axi.y][axi.x] && map[axi.y][axi.x] != asset)
			++axi.x;
		if (map[axi.y][axi.x] == asset)
			break ;
		++axi.y;
	}
	if (map[axi.y][axi.x] == asset)
		return (axi);
	return (ft_bzero(&axi, sizeof(axi)), axi);
}

static bool	flood_check(char **grid, t_axis limit)
{
	int		y;
	bool	result;

	result = false;
	if (ft_strchr(grid[0], 'F') || ft_strchr(grid[limit.y - 1], 'F'))
		result = true;
	y = 0;
	while (y < limit.y)
	{
		if ((ft_strchr(grid[y], 'C') || ft_strchr(grid[y], 'E')
				||grid[y][0] == 'F' || grid[y][limit.x - 1] == 'F')
				&& !result)
			result = true;
		free(grid[y++]);
	}
	return (free(grid), result);
}

static void	flood(char **grid, t_axis start, t_axis limit, bool path)
{
	if (start.x < 0 || start.y < 0)
		return ;
	if (start.x >= limit.x || start.y >= limit.y)
		return ;
	if (grid[start.y][start.x] == 'F' || grid[start.y][start.x] == '1'
		|| grid[start.y][start.x] == '\n' || grid[start.y][start.x] == '\0')
		return ;
	if (grid[start.y][start.x] == 'E' && path)
	{
		grid[start.y][start.x] = '1';
		return ;
	}
	grid[start.y][start.x] = 'F';
	flood(grid, (t_axis){start.x - 1, start.y}, limit, path);
	flood(grid, (t_axis){start.x + 1, start.y}, limit, path);
	flood(grid, (t_axis){start.x, start.y - 1}, limit, path);
	flood(grid, (t_axis){start.x, start.y + 1}, limit, path);
}

static char	**load_map(t_list *map, size_t map_y)
{
	size_t	i;
	char	**grid;

	grid = malloc(sizeof(char *) * map_y);
	if (!grid)
		return (NULL);
	i = 0;
	while (map && i < map_y)
	{
		grid[i] = ft_strdup(map->content);
		if (!grid[i++])
		{
			while (i--)
				free(grid[i]);
			return (free(grid), NULL);
		}
		map = map->next;
	}
	return (grid);
}

bool	flood_fill(t_list *map)
{
	char	**grid;
	size_t	map_y;
	t_axis	axis[2];

	map_y = get_height(map);
	grid = load_map(map, map_y);
	if (!grid)
		return (print_error("Memory allocation failure!"), true);
	axis[0] = find_asset(grid, map_y, 'P');
	axis[1] = ((t_axis){ft_strlen(grid[0]) - 1, map_y});
	flood(grid, axis[0], axis[1], true);
	if (flood_check(grid, axis[1]))
		return (print_error("Invalid map"), true);
	grid = load_map(map, map_y);
	if (!grid)
		return (print_error("Memory allocation failure!"), true);
	flood(grid, axis[0], axis[1], false);
	if (!flood_check(grid, axis[1]))
		return (false);
	return (print_error("The map must be closed/surrounded by walls"), true);
}
