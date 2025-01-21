/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a1_event_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:17:39 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/21 12:38:36 by josfelip         ###   ########.fr       */
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
	t_mlx			*win;
	double			current_time;
	static double	last_time;

	win = (t_mlx *)param;
	current_time = mlx_get_time();
	if (current_time - last_time < 1.0 / FRAME_RATE)
		return ;
	if (mlx_is_key_down(win->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(win->mlx);
	update_player_position(&win->player, &win->scene->map, win->mlx);
	render_frame(win);
	last_time = current_time;
}

void	init_hooks(t_mlx *win)
{
	mlx_close_hook(win->mlx, &close_window, win);
	mlx_loop_hook(win->mlx, &game_loop, win);
}
