/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:13:41 by josfelip          #+#    #+#             */
/*   Updated: 2024/11/19 23:26:12 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser.h"

static int is_valid_map_char(char c);
static int init_scene(t_scene *scene);
static int process_line(char *line, t_scene *scene, int fd);

int parse_scene(char *file_path, t_scene *scene)
{
    int     fd;
    char    *line;

    if (!check_file_extension(file_path))
        return (write(2, ERROR_FILE_EXT, ft_strlen(ERROR_FILE_EXT)));
    fd = open(file_path, O_RDONLY);
    if (fd < 0)
        return (write(2, ERROR_FILE_OPEN, ft_strlen(ERROR_FILE_OPEN)));
    init_scene(scene);
    while (get_next_line(fd, &line))
    {
        if (!process_line(line, scene, fd))
            return (0);
        free(line);
    }
    close(fd);
    return (1);
}

static int is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || 
            c == 'E' || c == 'W' || c == ' ');
}

static int init_scene(t_scene *scene)
{
    scene->textures.north = NULL;
    scene->textures.south = NULL;
    scene->textures.west = NULL;
    scene->textures.east = NULL;
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
    if (line[0] == 'N' || line[0] == 'S' || 
        line[0] == 'W' || line[0] == 'E')
        return (parse_textures(line, scene));
    else if (line[0] == 'F' || line[0] == 'C')
        return (parse_colors(line, scene));
    else if (is_valid_map_char(line[0]))
        return (parse_map(fd, scene));
    return (1);
}

