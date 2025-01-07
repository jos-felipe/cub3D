/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a2_player_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:00:00 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/07 16:23:22 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch1_window_management.h"

static void	set_initial_direction(t_player *player, char direction);
static void	set_direction_ns(t_player *player, char direction);
static void	set_direction_ew(t_player *player, char direction);

void	init_player(t_player *player, t_map *map)
{
	player->pos_x = map->player_x + 0.5;
	player->pos_y = map->player_y + 0.5;
	set_initial_direction(player, map->player_dir);
}

static void	set_initial_direction(t_player *player, char direction)
{
	if (direction == 'N' || direction == 'S')
		set_direction_ns(player, direction);
	else if (direction == 'E' || direction == 'W')
		set_direction_ew(player, direction);
}

static void	set_direction_ns(t_player *player, char direction)
{
	if (direction == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (direction == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
}

static void	set_direction_ew(t_player *player, char direction)
{
	if (direction == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (direction == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
}
