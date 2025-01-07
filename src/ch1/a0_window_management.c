/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a0_window_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:17:39 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/07 16:17:09 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch1_window_management.h"

static int	create_window(t_mlx *win);
static int	create_image(t_mlx *win);

int	init_window(t_mlx *win, t_scene *scene)
{
	win->scene = scene;
	win->width = WINDOW_WIDTH;
	win->height = WINDOW_HEIGHT;
	if (create_window(win) != 0)
		return (1);
	if (create_image(win) != 0)
	{
		mlx_terminate(win->mlx);
		return (1);
	}
	init_player(&win->player, &scene->map);
	init_hooks(win);
	return (0);
}

static int	create_window(t_mlx *win)
{
	mlx_set_setting(MLX_MAXIMIZED, false);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	win->mlx = mlx_init(win->width, win->height, WINDOW_TITLE, false);
	if (!win->mlx)
	{
		ft_putstr_fd(mlx_strerror(mlx_errno), 2);
		return (1);
	}
	return (0);
}

static int	create_image(t_mlx *win)
{
	win->img = mlx_new_image(win->mlx, win->width, win->height);
	if (!win->img)
	{
		ft_putstr_fd(mlx_strerror(mlx_errno), 2);
		return (1);
	}
	if (mlx_image_to_window(win->mlx, win->img, 0, 0) == -1)
	{
		ft_putstr_fd(mlx_strerror(mlx_errno), 2);
		mlx_delete_image(win->mlx, win->img);
		return (1);
	}
	return (0);
}

void	cleanup_window(t_mlx *win)
{
	if (!win)
		return ;
	if (win->mlx)
	{
		mlx_delete_image(win->mlx, win->img);
		mlx_terminate(win->mlx);
	}
}
