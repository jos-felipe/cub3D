/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch0_scene_description_file.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:13:13 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/14 17:38:13 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CH0_SCENE_DESCRIPTION_FILE_H
# define CH0_SCENE_DESCRIPTION_FILE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../lib/libft/include/libft.h"
# include "cub3d_types.h"

extern const char	*g_error_messages[];

int		check_file_extension(char *file_path);
int		free_and_return(t_error code, char *s, char **ss);
int		parse_colors(char *line, t_scene *scene);
int		parse_map(int fd, char *line, t_scene *scene);
int		parse_scene(char *file_path, t_scene *scene);
int		parse_textures(char *line, t_scene *scene);
int		validate_map(t_map *map);
int		write2err_and_return(t_error code);
void	debug_scene(t_scene *scene);
void	free_scene(t_scene *scene);
void	write2err(t_error code, t_scene *maze);

#endif
