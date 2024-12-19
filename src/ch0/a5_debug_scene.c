/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a5_debug_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:13:41 by josfelip          #+#    #+#             */
/*   Updated: 2024/12/19 11:54:10 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch0_scene_description_file.h"

void	debug_scene(t_scene *scene)
{
	int	i;
	int	j;

	ft_printf("NORTH: %s\n", scene->textures.north);
	ft_printf("SOUTH: %s\n", scene->textures.south);
	ft_printf("WEST: %s\n", scene->textures.west);
	ft_printf("EAST: %s\n", scene->textures.east);
	ft_printf("FLOOR: %d %d %d\n", scene->floor.r, scene->floor.g,
		scene->floor.b);
	ft_printf("CEILING: %d %d %d\n", scene->ceiling.r, scene->ceiling.g,
		scene->ceiling.b);
	ft_printf("MAP:\n");
	i = -1;
	while (++i < scene->map.height)
	{
		j = -1;
		while (++j < scene->map.width)
			ft_printf("%c", scene->map.grid[i][j]);
		ft_printf("\n");
	}
	ft_printf("PLAYER: %d %d %c\n", scene->map.player_x, scene->map.player_y,
		scene->map.player_dir);
}
