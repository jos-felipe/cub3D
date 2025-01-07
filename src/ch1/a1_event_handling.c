/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a1_event_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:17:39 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/07 16:54:13 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch1_window_management.h"

static void	close_window(void *param)
{
	t_mlx	*win;

	win = (t_mlx *)param;
	mlx_close_window(win->mlx);
}

static void	game_loop(void *param)
{
	t_mlx	*win;

	win = (t_mlx *)param;
	if (mlx_is_key_down(win->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(win->mlx);
	update_player_position(&win->player, &win->scene->map, win->mlx);
	update_test_view(win);
}

void	init_hooks(t_mlx *win)
{
	mlx_close_hook(win->mlx, &close_window, win);
	mlx_loop_hook(win->mlx, &game_loop, win);
}
