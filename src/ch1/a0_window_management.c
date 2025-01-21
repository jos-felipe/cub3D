/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a0_window_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:00:00 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/21 16:24:47 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch1_window_management.h"

static int	create_window(t_mlx *win);
static int	create_image(t_mlx *win);
static int	init_resources(t_mlx *win);

int	init_window(t_mlx *win, t_scene *scene)
{
	win->scene = scene;
	win->width = WINDOW_WIDTH;
	win->height = WINDOW_HEIGHT;
	if (create_window(win) != 0)
		return (1);
	if (init_resources(win) != 0)
	{
		cleanup_window(win);
		return (1);
	}
	init_player(&win->player, &scene->map);
	init_hooks(win);
	initialize_rendering(win);
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

static int	init_resources(t_mlx *win)
{
	if (create_image(win) != 0)
		return (1);
	if (load_textures(win) != 0)
	{
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
		cleanup_textures(&win->textures);
		mlx_delete_image(win->mlx, win->img);
		mlx_terminate(win->mlx);
	}
}
