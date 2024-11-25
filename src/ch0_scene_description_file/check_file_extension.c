/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_extension.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:13:41 by josfelip          #+#    #+#             */
/*   Updated: 2024/11/21 12:02:59 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_description_file.h"

int check_file_extension(char *file_path)
{
    size_t  len;
    char    *ext;

    if (!file_path)
        return (1);
    len = ft_strlen(file_path);
    if (len < 4)
        return (1);
    ext = file_path + len - 4;
    return (ft_strncmp(ext, ".cub", 4));
}
