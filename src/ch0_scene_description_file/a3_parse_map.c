/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a3_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:40:12 by josfelip          #+#    #+#             */
/*   Updated: 2024/11/28 15:17:35 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ch0_scene_description_file.h"

static char **normalize_grid(char **grid,  t_map *map);
static char **realloc_map(char **map, int height);
static  int is_a_valid_map_line(char *line);
static  int get_max_width(char **map);

int parse_map(int fd, t_scene *scene)
{
    char *line;
    char **temp_map;
    int height;
    
    height = 0;
    temp_map = ft_calloc(1, sizeof(char *));
    line = get_next_line(fd);
    while (line)
    {
        if (!is_a_valid_map_line(line))
        {
            free(line);
            return (write2err_and_2free(ERROR_MAP_CHARS, NULL, temp_map));
        }
        temp_map = realloc_map(temp_map, ++height);
        if (!temp_map)
            return (write2err_and_2free("MALLOC_ERROR", NULL, temp_map));
        temp_map[height - 1] = line;
        line = get_next_line(fd);
    }
    scene->map.height = height;
    scene->map.width = get_max_width(temp_map);
    scene->map.grid = normalize_grid(temp_map, &scene->map);
    ft_free_split(temp_map);
    return (validate_map(&scene->map));
}

static int    is_a_valid_map_line(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (!is_a_valid_map_char(line[i]))
            return (0);
        i++;
    }
    return (1);
}

static char    **realloc_map(char **old_map, int new_size)
{
    char    **new_map;
    int        i;

    new_map = ft_calloc(new_size + 1, sizeof(char *));
    if (!new_map)
        return (NULL);
    i = 0;
    while (i < new_size - 1)
    {
        new_map[i] = old_map[i];
        i++;
    }
    free(old_map);
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

static char **normalize_grid(char **grid,  t_map *map)
{
    char    **norm_grid;
    int     i;
    
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
