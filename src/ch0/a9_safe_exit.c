/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a9_safe_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 05:21:36 by josfelip          #+#    #+#             */
/*   Updated: 2024/12/04 17:00:13 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch0_scene_description_file.h"

int free_scene(t_scene *scene)
{
    free(scene->textures.north);
    free(scene->textures.south);
    free(scene->textures.west);
    free(scene->textures.east);
    ft_free_split(scene->map.grid);
    return (1);
}

int write2err_and_2free(t_error code, char **ss1, char **ss2)
{
    ft_free_split(ss1);
    ft_free_split(ss2);
    return (write2err_and_return(code));
}

int write2err_and_free(t_error code, char **ss1, char **ss2, char *line)
{
    ft_free_split(ss1);
    ft_free_split(ss2);
    free(line);
    return (write2err_and_return(code));
}

int write2err_and_return(t_error code)
{
    ft_putstr_fd(g_error_messages[code], 2);
    return (code);
}

void write2err(t_error code)
{
    if (code)
        ft_putstr_fd(g_error_messages[code], 2);
}

const char *g_error_messages[] = {
    "Success",
    "Error\nInvalid arguments\n",
    "Error\nInvalid file extension\n",
    "Error\nCould not open file\n",
    "Error\nInvalid map format\n",
    "Error\nInvalid texture path\n",
    "Error\nInvalid color format\n",
    "Error\nInvalid player position or multiple players\n",
    "Error\nInvalid map characters\n",
    "Error\nInvalid malloc\n",
    "Error\nInvalid identifier\n",
    "Error\nUndefined error\n",
};
