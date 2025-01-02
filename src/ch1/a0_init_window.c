/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a0_init_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:17:39 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/02 13:17:44 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch1_window.h"

int	init_window(t_window *window, t_scene *scene)
{
	window->scene = scene;
	window->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false);
	if (!window->mlx)
		return (write2err_and_return(UNDEFINED_ERROR));
	window->img = mlx_new_image(window->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!window->img)
	{
		mlx_terminate(window->mlx);
		return (write2err_and_return(UNDEFINED_ERROR));
	}
	if (mlx_image_to_window(window->mlx, window->img, 0, 0) == -1)
	{
		mlx_delete_image(window->mlx, window->img);
		mlx_terminate(window->mlx);
		return (write2err_and_return(UNDEFINED_ERROR));
	}
	mlx_loop_hook(window->mlx, game_loop, window);
	mlx_key_hook(window->mlx, handle_keys, window);
	return (0);
}

void	clean_window(t_window *window)
{
	if (window->img)
		mlx_delete_image(window->mlx, window->img);
	if (window->mlx)
		mlx_terminate(window->mlx);
}