/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a9_safe_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 05:21:36 by josfelip          #+#    #+#             */
/*   Updated: 2024/12/02 12:19:04 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch0_scene_description_file.h"

int free_heap(t_scene *scene)
{
    free(scene->textures.north);
    free(scene->textures.south);
    free(scene->textures.west);
    free(scene->textures.east);
    ft_free_split(scene->map.grid);
    return (1);
}

int write2err_and_2free(char *err_msg, char **ss1, char **ss2)
{
    ft_free_split(ss1);
    ft_free_split(ss2);
    return (write(2, err_msg, ft_strlen(err_msg)));
}

int write2err_and_return(char *err_msg, int ret)
{
    write(2, err_msg, ft_strlen(err_msg));
    return (ret);
}
