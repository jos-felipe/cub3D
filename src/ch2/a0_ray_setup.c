/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a0_ray_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:15:00 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/14 17:53:28 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch1_window_management.h"

static void	render_loop(void *param)
{
	t_mlx	*win;

	win = (t_mlx *)param;
	if (update_player_position(&win->player, &win->scene->map, win->mlx))
	{
		render_frame(win);
	}
}

void	init_ray_casting(t_mlx *win)
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

void	cast_rays(t_mlx *win)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < win->width)
	{
		calculate_ray_position(&ray, &win->player, x, win->width);
		calculate_step_distance(&ray, &win->player);
		perform_dda(&ray, &win->scene->map);
		calculate_wall_height(&ray, win->height);
		draw_vertical_line(win, &ray, x);
		x++;
	}
}
