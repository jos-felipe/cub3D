/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch0_scene_description_file.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:13:13 by josfelip          #+#    #+#             */
/*   Updated: 2024/12/18 09:23:24 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CH0_SCENE_DESCRIPTION_FILE_H
# define CH0_SCENE_DESCRIPTION_FILE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../lib/libft/include/libft.h"

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_textures;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;

typedef struct s_scene
{
	t_textures	textures;
	t_color		floor;
	t_color		ceiling;
	t_map		map;
}	t_scene;

typedef enum e_error
{
	INVALID_ARGS = 1,
	INVALID_FILE_EXT,
	INVALID_FD,
	INVALID_MAP,
	INVALID_TEXTURE,
	INVALID_COLOR,
	INVALID_PLAYER,
	INVALID_MAP_CHARS,
	INVALID_MALLOC,
	INVALID_IDENTIFIER,
	UNDEFINED_ERROR
}	t_error;

extern const char	*g_error_messages[];

int		check_file_extension(char *file_path);
int		free_and_return(t_error code, char *s, char **ss);
int		free_scene(t_scene *scene);
int		parse_colors(char *line, t_scene *scene);
int		parse_map(int fd, char *line, t_scene *scene);
int		parse_scene(char *file_path, t_scene *scene);
int		parse_textures(char *line, t_scene *scene);
int		validate_map(t_map *map);
int		write2err_and_return(t_error code);
void	debug_scene(t_scene *scene);
void	write2err(t_error code, t_scene *maze);

#endif
