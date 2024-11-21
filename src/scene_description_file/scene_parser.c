/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:13:41 by josfelip          #+#    #+#             */
/*   Updated: 2024/11/21 12:37:23 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_description_file.h"

static int init_scene(t_scene *scene);
static int process_line(char *line, t_scene *scene, int fd);
static int is_valid_map_char(char c);

int parse_scene(char *file_path, t_scene *scene)
{
    char    *line;
    int     fd;
    int     ret;

    ret = 0;
    if (check_file_extension(file_path))
        return (write(2, ERROR_FILE_EXT, ft_strlen(ERROR_FILE_EXT)));
    fd = open(file_path, O_RDONLY);
    if (fd < 0)
        return (write(2, ERROR_FILE_OPEN, ft_strlen(ERROR_FILE_OPEN)));
    init_scene(scene);
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
    return (ret);
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
    return (write(2, ERROR_MAP_CHARS, ft_strlen(ERROR_MAP_CHARS)));
}
static int is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || 
            c == 'E' || c == 'W' || c == ' ');
}


