/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a3_player_movement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:00:00 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/09 09:16:13 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch1_window_management.h"

static int	move_forward(t_player *player, t_map *map);
static int	move_backward(t_player *player, t_map *map);
static int	move_lateral(t_player *player, t_map *map, int direction);

int	update_player_position(t_player *player, t_map *map, mlx_t *mlx)
{
	int	moved;

	moved = 0;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		moved |= move_forward(player, map);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		moved |= move_backward(player, map);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		moved |= move_lateral(player, map, -1);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		moved |= move_lateral(player, map, 1);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		rotate_player(player, -ROT_SPEED);
		moved = 1;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		rotate_player(player, ROT_SPEED);
		moved = 1;
	}
	return (moved);
}

static int	move_forward(t_player *player, t_map *map)
{
	double	new_x;
	double	new_y;
	int		moved;

	moved = 0;
	new_x = player->pos_x + player->dir_x * MOVE_SPEED;
	new_y = player->pos_y + player->dir_y * MOVE_SPEED;
	if (!check_collision(map, new_x, player->pos_y))
	{
		player->pos_x = new_x;
		moved = 1;
	}
	if (!check_collision(map, player->pos_x, new_y))
	{
		player->pos_y = new_y;
		moved = 1;
	}
	return (moved);
}

static int	move_backward(t_player *player, t_map *map)
{
	double	new_x;
	double	new_y;
	int		moved;

	moved = 0;
	new_x = player->pos_x - player->dir_x * MOVE_SPEED;
	new_y = player->pos_y - player->dir_y * MOVE_SPEED;
	if (!check_collision(map, new_x, player->pos_y))
	{
		player->pos_x = new_x;
		moved = 1;
	}
	if (!check_collision(map, player->pos_x, new_y))
	{
		player->pos_y = new_y;
		moved = 1;
	}
	return (moved);
}

static int	move_lateral(t_player *player, t_map *map, int direction)
{
	double	new_x;
	double	new_y;
	int		moved;

	moved = 0;
	new_x = player->pos_x + (direction * player->plane_x * MOVE_SPEED);
	new_y = player->pos_y + (direction * player->plane_y * MOVE_SPEED);
	if (!check_collision(map, new_x, player->pos_y))
	{
		player->pos_x = new_x;
		moved = 1;
	}
	if (!check_collision(map, player->pos_x, new_y))
	{
		player->pos_y = new_y;
		moved = 1;
	}
	return (moved);
}
