/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a1_check_file_extension.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:13:41 by josfelip          #+#    #+#             */
/*   Updated: 2024/12/18 10:01:59 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch0_scene_description_file.h"

int	check_file_extension(char *file_path)
{
	char	*ext;
	size_t	len;

	len = ft_strlen(file_path);
	if (len <= 4)
		return (1);
	ext = file_path + len - 4;
	return (ft_strncmp(ext, ".cub", 4));
}
