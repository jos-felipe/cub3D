/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a3_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:40:12 by josfelip          #+#    #+#             */
/*   Updated: 2024/12/18 13:50:45 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch0_scene_description_file.h"

static char	**normalize_grid(char **grid, t_map *map);
static char	**realloc_grid(char **map, int height);
static int	get_max_width(char **map);
static int	is_valid_map_line(char *line);

int	parse_map(int fd, char *line, t_scene *scene)
{
	char	*gnl;
	char	**grid;
	char	*trimmed;

	grid = ft_calloc(1, sizeof(char *));
	trimmed = ft_strtrim(line, "\n");
	while (trimmed)
	{
		if (!is_valid_map_line(trimmed))
			return (free_and_return(INVALID_MAP_CHARS, trimmed, grid));
		grid = realloc_grid(grid, ++scene->map.height);
		if (!grid)
			return (free_and_return(INVALID_MALLOC, trimmed, grid));
		grid[scene->map.height - 1] = trimmed;
		gnl = get_next_line(fd);
		trimmed = ft_strtrim(gnl, "\n");
		free(gnl);
	}
	scene->map.width = get_max_width(grid);
	scene->map.grid = normalize_grid(grid, &scene->map);
	ft_free_split(grid);
	return (validate_map(&scene->map));
}

static int	is_valid_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("0NSEW1 ", line[i]))
			return (0);
		i++;
	}
	return (1);
}

static char	**realloc_grid(char **old_grid, int new_size)
{
	char	**new_map;
	int		i;

	new_map = ft_calloc(new_size + 1, sizeof(char *));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < new_size - 1)
	{
		new_map[i] = old_grid[i];
		i++;
	}
	free(old_grid);
	return (new_map);
}

static int    get_max_width(char **map)
{
	int    max_width;
	int    current_width;
	int    i;

	if (!map)
		return (0);
	max_width = 0;
	i = 0;
	while (map[i])
	{
		current_width = 0;
		while (map[i][current_width])
			current_width++;
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	return (max_width);
}

static char	**normalize_grid(char **grid, t_map *map)
{
	char	**norm_grid;
	int		i;

	norm_grid = ft_calloc(map->height + 1, sizeof(char *));
	if (!norm_grid)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		norm_grid[i] = ft_calloc(map->width + 1, sizeof(char));
		if (!norm_grid[i])
			return (NULL);
		ft_memset(norm_grid[i], ' ', map->width);
		ft_memcpy(norm_grid[i], grid[i], ft_strlen(grid[i]));
		i++;
	}
	return (norm_grid);
}
