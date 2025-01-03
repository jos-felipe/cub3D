/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a1_event_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:17:39 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/02 17:38:13 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch1_window_management.h"

static void	handle_keypress(mlx_key_data_t keydata, void *param);

void	init_hooks(t_mlx *win)
{
	mlx_key_hook(win->mlx, handle_keypress, win);
}

void	handle_keypress(mlx_key_data_t keydata, void *param)
{
	t_mlx	*win;

	win = (t_mlx *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(win->mlx);
}

