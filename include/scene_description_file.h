/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_description_file.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:13:13 by josfelip          #+#    #+#             */
/*   Updated: 2024/11/21 11:41:48 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_DESCRIPTION_FILE_H
# define SCENE_DESCRIPTION_FILE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"

# define ERROR_FILE_EXT "Error\nInvalid file extension. Must be .cub"
# define ERROR_FILE_OPEN "Error\nCould not open the file"
# define ERROR_INVALID_MAP "Error\nMap is not properly closed by walls"
# define ERROR_INVALID_TEXTURE "Error\nInvalid texture path"
# define ERROR_INVALID_COLOR "Error\nInvalid color format"
# define ERROR_INVALID_PLAYER "Error\nInvalid player position or multiple players"
# define ERROR_MAP_CHARS "Error\nInvalid characters in map"

typedef struct s_color
{
    int r;
    int g;
    int b;
}   t_color;

typedef struct s_textures
{
    char    *north;
    char    *south;
    char    *west;
    char    *east;
}   t_textures;

typedef struct s_map
{
    char    **grid;
    int     width;
    int     height;
    int     player_x;
    int     player_y;
    char    player_dir;
}   t_map;

typedef struct s_scene
{
    t_textures  textures;
    t_color     floor;
    t_color     ceiling;
    t_map       map;
}   t_scene;

/* Function prototypes */
int     parse_scene(char *file_path, t_scene *scene);
int     check_file_extension(char *file_path);
int     parse_textures(char *line, t_scene *scene);
int     parse_colors(char *line, t_scene *scene);
int     parse_map(int fd, t_scene *scene);
int     validate_map(t_map *map);

#endif
