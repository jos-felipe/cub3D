/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch0_scene_description_file.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:13:13 by josfelip          #+#    #+#             */
/*   Updated: 2024/11/28 11:25:28 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CH0_SCENE_DESCRIPTION_FILE_H
# define CH0_SCENE_DESCRIPTION_FILE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../lib/libft/include/libft.h"
# include "../lib/libft/include/get_next_line_bonus.h"

# define ERROR_FILE_EXT "Error\nInvalid file extension. Must be .cub\n"
# define ERROR_FILE_OPEN "Error\nCould not open the file\n"
# define ERROR_INVALID_MAP "Error\nMap is not properly closed by walls\n"
# define ERROR_INVALID_TEXTURE "Error\nInvalid texture path\n"
# define ERROR_INVALID_COLOR "Error\nInvalid color format\n"
# define ERROR_INVALID_PLAYER "Error\nInvalid player position or multiple players\n"
# define ERROR_MAP_CHARS "Error\nInvalid characters in map\n"

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

int     check_file_extension(char *file_path);
int     is_a_valid_map_char(char c);
int     parse_textures(char *line, t_scene *scene);
int     parse_colors(char *line, t_scene *scene);
int     parse_map(int fd, t_scene *scene);
int     parse_scene(char *file_path, t_scene *scene);
int     validate_map(t_map *map);
int     write2err_and_2free(char *err_msg, char **ss1, char **ss2);

#endif
