/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a2_parse_decorators.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:40:12 by josfelip          #+#    #+#             */
/*   Updated: 2024/11/25 16:02:09 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch0_scene_description_file.h"

static  int is_valid_color(t_color *color, char **rgb);
static  int write2err_and_2free(char **rgb, char **split);

int parse_textures(char *line, t_scene *scene)
{
    char    **split;
    int     ret;

    ret = 0;
    split = ft_split(line, ' ');
    if (!split | !split[0] || !split[1])
        ret = write(2, ERROR_INVALID_TEXTURE, 
                ft_strlen(ERROR_INVALID_TEXTURE));
    else
    {
        if (ft_strncmp(split[0], "NO", 2) == 0)
            scene->textures.north = ft_strdup(split[1]);
        else if (ft_strncmp(split[0], "SO",2) == 0)
            scene->textures.south = ft_strdup(split[1]);
        else if (ft_strncmp(split[0], "WE",2) == 0)
            scene->textures.west = ft_strdup(split[1]);
        else if (ft_strncmp(split[0], "EA",2) == 0)
            scene->textures.east = ft_strdup(split[1]);
        else
            ret = write(2, ERROR_INVALID_TEXTURE, 
                ft_strlen(ERROR_INVALID_TEXTURE));
    }
    ft_free_split(split);
    return (ret);
}

int parse_colors(char *line, t_scene *scene)
{
    char    **split;
    char    **rgb;
    t_color *color;

    split = ft_split(line, ' ');
    if (!split || !split[0] || !split[1])
        return (write2err_and_2free(NULL, split));
    if (split[0][0] == 'F')
        color = &scene->floor;
    else
        color = &scene->ceiling;
    rgb = ft_split(split[1], ',');
    if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
        return (write2err_and_2free(rgb, split));
    if (!is_valid_color(color, rgb))
        return (write2err_and_2free(rgb, split));
    ft_free_split(rgb);
    ft_free_split(split);
    return (0);
}

static  int is_valid_color(t_color *color, char **rgb)
{
    int r;
    int g;
    int b;

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

static  int write2err_and_2free(char **rgb, char **split)
{
    ft_free_split(rgb);
    ft_free_split(split);
    return (write(2, ERROR_INVALID_COLOR, ft_strlen(ERROR_INVALID_COLOR)));
}

int write2err_and_2free(char *err_msg, char **ss1, char **ss2)
{
    ft_free_split(ss1);
    ft_free_split(ss2);
    return (write(2, err_msg, ft_strlen(err_msg)));
}