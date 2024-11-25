/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:40:12 by josfelip          #+#    #+#             */
/*   Updated: 2024/11/25 13:33:04 by josfelip         ###   ########.fr       */
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

