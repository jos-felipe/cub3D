/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a0_parse_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:13:41 by josfelip          #+#    #+#             */
/*   Updated: 2024/12/04 17:04:50 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch0_scene_description_file.h"

static int  init_scene(t_scene *scene);
static int  process_line(char *line, t_scene *scene, int fd);
static int  completeness_check(t_scene *scene);

int parse_scene(char *file_path, t_scene *scene)
{
    char    *line;
    int     fd;
    int     ret;

    ret = INVALID_IDENTIFIER;
    init_scene(scene);
    if (check_file_extension(file_path))
        return (INVALID_FILE_EXT);
    fd = open(file_path, O_RDONLY);
    if (fd < 0)
        return (INVALID_FD);
    line = get_next_line(fd);
    while (line)
    {
        ret = process_line(line, scene, fd);
        free(line);
        if (ret)
            break ;
        line = get_next_line(fd);
    }
    close(fd);
    if (!ret)
        ret = completeness_check(scene);
    return (ret);
}

static int init_scene(t_scene *scene)
{
    scene->textures.north = NULL;
    scene->textures.south = NULL;
    scene->textures.west = NULL;
    scene->textures.east = NULL;
    scene->floor.r = -1;
    scene->floor.g = -1;
    scene->floor.b = -1;
    scene->ceiling.r = -1;
    scene->ceiling.g = -1;
    scene->ceiling.b = -1;
    scene->map.grid = NULL;
    scene->map.width = 0;
    scene->map.height = 0;
    scene->map.player_x = -1;
    scene->map.player_y = -1;
    scene->map.player_dir = '\0';
    return (1);
}

static int process_line(char *line, t_scene *scene, int fd)
{
    static int  map_started = 0;
    
    if (!map_started && line[0] == '\n')
        return (0);
    if (ft_strchr("NSWE", line[0]))
        return (parse_textures(line, scene));
    if (ft_strchr("FC", line[0]))
        return (parse_colors(line, scene));
    if (ft_strchr("1 ", line[0]))
    {
        map_started = 1;
        return (parse_map(fd, scene));
    }
    return (INVALID_IDENTIFIER);
}

int is_a_valid_map_char(char c)
{
    int ret;

    ret = 0;
    if (ft_strchr("0NSEW1 ", c))
        ret = 1;
    return (ret);
}

static int  completeness_check(t_scene *scene)
{
    if (!scene->textures.north || !scene->textures.south || 
        !scene->textures.west || !scene->textures.east)
        return (UNDEFINED_ERROR);
    if (scene->floor.r == -1 || scene->floor.g == -1 || 
        scene->floor.b == -1 || scene->ceiling.r == -1 || 
        scene->ceiling.g == -1 || scene->ceiling.b == -1)
        return (UNDEFINED_ERROR);
    if (!scene->map.grid || scene->map.width == 0 || 
        scene->map.height == 0 || scene->map.player_x == -1 || 
        scene->map.player_y == -1 || scene->map.player_dir == '\0')
        return (UNDEFINED_ERROR);
    return (0);
}
