/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a5_test_unit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:00:00 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/07 16:51:55 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch1_window_management.h"

#define CELL_SIZE 32
#define PLAYER_SIZE 8

static void	draw_cell(mlx_image_t *img, int x, int y, uint32_t color)
{
	int	i;
	int	j;
	int	px;
	int	py;

	i = 0;
	while (i < CELL_SIZE)
	{
		j = 0;
		while (j < CELL_SIZE)
		{
			px = x * CELL_SIZE + i;
			py = y * CELL_SIZE + j;
			mlx_put_pixel(img, px, py, color);
			j++;
		}
		i++;
	}
}

static void	draw_player(mlx_image_t *img, t_player *player)
{
	int		i;
	int		j;
	int		px;
	int		py;
	double	screen_x;
	double	screen_y;

	screen_x = player->pos_x * CELL_SIZE;
	screen_y = player->pos_y * CELL_SIZE;
	i = -PLAYER_SIZE / 2;
	while (i < PLAYER_SIZE / 2)
	{
		j = -PLAYER_SIZE / 2;
		while (j < PLAYER_SIZE / 2)
		{
			px = screen_x + i;
			py = screen_y + j;
			mlx_put_pixel(img, px, py, 0xFF0000FF);
			j++;
		}
		i++;
	}
}

void	draw_direction(mlx_image_t *img, t_player *player)
{
	int		i;
	double	start_x;
	double	start_y;
	double	end_x;
	double	end_y;

	start_x = player->pos_x * CELL_SIZE;
	start_y = player->pos_y * CELL_SIZE;
	end_x = start_x + player->dir_x * CELL_SIZE;
	end_y = start_y + player->dir_y * CELL_SIZE;
	i = 0;
	while (i < CELL_SIZE)
	{
		mlx_put_pixel(img, start_x + player->dir_x * i,
			start_y + player->dir_y * i, 0x00FF00FF);
		i++;
	}
}

void	update_test_view(t_mlx *win)
{
	int	x;
	int	y;

	ft_memset(win->img->pixels, 0, win->img->width
		* win->img->height * sizeof(int32_t));
	y = 0;
	while (y < win->scene->map.height)
	{
		x = 0;
		while (x < win->scene->map.width)
		{
			if (win->scene->map.grid[y][x] == '1')
				draw_cell(win->img, x, y, 0xFFFFFFFF);
			x++;
		}
		y++;
	}
	draw_player(win->img, &win->player);
	draw_direction(win->img, &win->player);
}
