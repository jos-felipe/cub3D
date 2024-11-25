/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a3_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:40:12 by josfelip          #+#    #+#             */
/*   Updated: 2024/11/25 13:24:41 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch0_scene_description_file.h"

static  int is_line_valid(char *line);
static  int get_max_width(char **map);
static  char **realloc_map(char **map, int height);
static  void normalize_map(char **map, t_scene *scene);

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
        if (!is_line_valid(line))
        {
            free(line);
            ft_free_split(temp_map);
            return(write(2, ERROR_MAP_CHARS, ft_strlen(ERROR_MAP_CHARS)));
        }
        temp_map = realloc_map(temp_map, ++height);
        temp_map[height - 1] = line;
        line = get_next_line(fd);
    }
    scene->map.height = height;
    scene->map.width = get_max_width(temp_map);
    normalize_map(temp_map, scene);
    ft_free_split(temp_map);
    return (validate_map(&scene->map));
}

static int    is_line_valid(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != '0' && line[i] != '1' && line[i] != ' ' 
            && line[i] != 'N' && line[i] != 'S' 
            && line[i] != 'E' && line[i] != 'W')
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

static  void normalize_map(char **map, t_scene *scene)
{
    int i;
    
    scene->map.grid = ft_calloc(scene->map.height, sizeof(char *));
    i = 0;
    while (i < scene->map.height)
    {
        scene->map.grid[i] = ft_calloc(scene->map.width, sizeof(char));
        ft_memset(scene->map.grid[i], ' ', scene->map.width);
        ft_memcpy(scene->map.grid[i], map[i], ft_strlen(map[i]));
        i++;
    }
}