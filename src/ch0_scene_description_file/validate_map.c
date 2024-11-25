/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:40:12 by josfelip          #+#    #+#             */
/*   Updated: 2024/11/21 16:19:10 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_description_file.h"

static int check_surrounding_walls(t_map *map, int i, int j);
static int process_map_char(t_map *map, int i, int j, int *player_count);

int validate_map(t_map *map)
{
    int i;
    int j;
    int player_count;

    player_count = 0;
    i = -1;
    while (++i < map->height)
    {
        j = -1;
        while (++j < map->width)
            if (!process_map_char(map, i, j, &player_count))
                return (write(2, ERROR_INVALID_MAP, 
                        ft_strlen(ERROR_INVALID_MAP)));
    }
    if (player_count != 1)
        return (write(2, ERROR_INVALID_PLAYER, 
                ft_strlen(ERROR_INVALID_PLAYER)));
    return (1);
}

static int check_surrounding_walls(t_map *map, int i, int j)
{
    if (i <= 0 || i >= map->height - 1 || j <= 0 || j >= map->width - 1)
        return (0);
    if (map->grid[i - 1][j] == ' ' || map->grid[i + 1][j] == ' ' ||
        map->grid[i][j - 1] == ' ' || map->grid[i][j + 1] == ' ')
        return (0);
    return (1);
}

static int process_map_char(t_map *map, int i, int j, int *player_count)
{
    char c;

    c = map->grid[i][j];
    if (c == ' ')
    {
        if (!check_surrounding_walls(map, i, j))
            return (0);
    }
    else if (ft_strchr("NSEW", c))
    {
        if (++(*player_count) > 1)
            return (0);
        map->player_x = j;
        map->player_y = i;
        map->player_dir = c;
    }
    else if (c != '0' && c != '1')
        return (0);
    return (1);
}


int parse_textures(char *line, t_scene *scene)
{
    char **split;
    int ret;

    ret = 0;
    split = ft_split(line, ' ');
    if (!split[0] || !split[1])
        return (write(2, ERROR_INVALID_TEXTURE, 
                ft_strlen(ERROR_INVALID_TEXTURE)));

    if (ft_strcmp(split[0], "NO") == 0)
        scene->textures.north = ft_strdup(split[1]);
    else if (ft_strcmp(split[0], "SO") == 0)
        scene->textures.south = ft_strdup(split[1]);
    else if (ft_strcmp(split[0], "WE") == 0)
        scene->textures.west = ft_strdup(split[1]);
    else if (ft_strcmp(split[0], "EA") == 0)
        scene->textures.east = ft_strdup(split[1]);
    else
        ret = 1;
    ft_free_split(split);
    return (ret);
}

int parse_colors(char *line, t_scene *scene)
{
    char **split;
    char **rgb;
    t_color *color;

    split = ft_split(line, ' ');
    if (!split[0] || !split[1])
        return (write(2, ERROR_INVALID_COLOR, ft_strlen(ERROR_INVALID_COLOR)));
    if (split[0][0] == 'F')
        color = &scene->floor;
    else
        color = &scene->ceiling;
    rgb = ft_split(split[1], ',');
    color->r = ft_atoi(rgb[0]);
    color->g = ft_atoi(rgb[1]);
    color->b = ft_atoi(rgb[2]);
    if (color->r < 0 || color->r > 255 || 
        color->g < 0 || color->g > 255 || 
        color->b < 0 || color->b > 255)
        return (write(2, ERROR_INVALID_COLOR, ft_strlen(ERROR_INVALID_COLOR)));
    ft_free_split(rgb);
    ft_free_split(split);
    return (0);
}
