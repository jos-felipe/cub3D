/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a0_ray_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:15:00 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/21 16:36:59 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch2_ray_casting.h"

static void	render_loop(void *param);

void	initialize_rendering(t_mlx *win)
{
	win->img = mlx_new_image(win->mlx, win->width, win->height);
	if (!win->img)
		return ;
	if (mlx_image_to_window(win->mlx, win->img, 0, 0) == -1)
	{
		mlx_delete_image(win->mlx, win->img);
		return ;
	}
	render_frame(win);
	mlx_loop_hook(win->mlx, render_loop, win);
}

static void	render_loop(void *param)
{
	t_mlx	*win;

	win = (t_mlx *)param;
	if (update_player_position(&win->player, &win->scene->map, win->mlx))
	{
		render_frame(win);
	}
}
