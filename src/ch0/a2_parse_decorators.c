/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a2_parse_decorators.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:40:12 by josfelip          #+#    #+#             */
/*   Updated: 2024/12/18 10:25:13 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch0_scene_description_file.h"

static char	*validate_path(char *path);
static int	free2split(t_error code, char **ss1, char **ss2);
static int	is_valid_color(t_color *color, char **rgb);

int	parse_textures(char *line, t_scene *scene)
{
	char	*path;
	char	**split;
	int		ret;

	ret = 0;
	split = ft_split(line, ' ');
	if (!split | !split[0] || !split[1])
		return (free2split(INVALID_TEXTURE, split, NULL));
	path = validate_path(split[1]);
	if (!path)
		return (free2split(INVALID_TEXTURE, split, NULL));
	if (ft_strncmp(split[0], "NO", 2) == 0)
		scene->textures.north = path;
	else if (ft_strncmp(split[0], "SO", 2) == 0)
		scene->textures.south = path;
	else if (ft_strncmp(split[0], "WE", 2) == 0)
		scene->textures.west = path;
	else if (ft_strncmp(split[0], "EA", 2) == 0)
		scene->textures.east = path;
	else
		ret = INVALID_TEXTURE;
	return (free2split(ret, split, NULL));
}

int	parse_colors(char *line, t_scene *scene)
{
	char	**split;
	char	**rgb;
	t_color	*color;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1])
		return (free2split(INVALID_COLOR, split, NULL));
	if (split[0][0] == 'F')
		color = &scene->floor;
	else
		color = &scene->ceiling;
	rgb = ft_split(split[1], ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (free2split(INVALID_COLOR, rgb, split));
	if (!is_valid_color(color, rgb))
		return (free2split(INVALID_COLOR, rgb, split));
	return (free2split(0, rgb, split));
}

static char	*validate_path(char *path)
{
	char	*trimmed;

	trimmed = ft_strtrim(path, "\n");
	if (access(trimmed, R_OK))
	{
		free(trimmed);
		return (NULL);
	}
	return (trimmed);
}

static int	is_valid_color(t_color *color, char **rgb)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	color->r = r;
	color->g = g;
	color->b = b;
	return (1);
}

static int	free2split(t_error code, char **ss1, char **ss2)
{
	ft_free_split(ss1);
	ft_free_split(ss2);
	return (code);
}
