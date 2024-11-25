/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a1_parse_decorators.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:40:12 by josfelip          #+#    #+#             */
/*   Updated: 2024/11/25 11:26:31 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch0_scene_description_file.h"

int parse_textures(char *line, t_scene *scene)
{
    char    **split;
    int     ret;

    ret = 0;
    split = ft_split(line, ' ');
    if (!split[0] || !split[1])
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
    if (!split[0] || !split[1])
        return (write(2, ERROR_INVALID_COLOR, ft_strlen(ERROR_INVALID_COLOR)));
    if (split[0][0] == 'F')
        color = &scene->floor;
    else
        color = &scene->ceiling;
    rgb = ft_split(split[1], ',');
    color->r = ft_atoi(rgb[0]);
    color->g = ft_atoi(rgb[1]);
    color->b = ft_atoi(rgb[2]);
    if (color->r < 0 || color->r > 255 || 
        color->g < 0 || color->g > 255 || 
        color->b < 0 || color->b > 255)
        return (write(2, ERROR_INVALID_COLOR, ft_strlen(ERROR_INVALID_COLOR)));
    ft_free_split(rgb);
    ft_free_split(split);
    return (0);
}
