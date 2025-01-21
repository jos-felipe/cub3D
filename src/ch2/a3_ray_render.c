/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a3_ray_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:00:00 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/21 15:56:00 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch2_ray_casting.h"

static void	draw_ceiling(t_mlx *win, int x, int draw_start)
{
	int			y;
	uint32_t	color;

	color = ((win->scene->ceiling.r & 0xff) << 24)
		| ((win->scene->ceiling.g & 0xff) << 16)
		| ((win->scene->ceiling.b & 0xff) << 8)
		| (0xff);
	y = 0;
	while (y < draw_start)
	{
		mlx_put_pixel(win->img, x, y, color);
		y++;
	}
}

static void	draw_floor(t_mlx *win, int x, int draw_end)
{
	int			y;
	uint32_t	color;

	color = ((win->scene->floor.r & 0xff) << 24)
		| ((win->scene->floor.g & 0xff) << 16)
		| ((win->scene->floor.b & 0xff) << 8)
		| (0xff);
	y = draw_end + 1;
	while (y < win->height)
	{
		mlx_put_pixel(win->img, x, y, color);
		y++;
	}
}

void	draw_vertical_line(t_mlx *win, t_ray *ray, int x)
{
	draw_ceiling(win, x, ray->draw_start);
	draw_wall(win, ray, x);
	draw_floor(win, x, ray->draw_end);
}

void	render_frame(t_mlx *win)
{
	int		x;
	t_ray	ray;

	ft_bzero(win->img->pixels, win->width * win->height * sizeof(int32_t));
	x = 0;
	while (x < win->width)
	{
		initialize_ray(&ray, &win->player, x, win->width);
		calculate_step_distance(&ray, &win->player);
		perform_dda(&ray, &win->scene->map);
		calculate_wall_height(&ray, win->height);
		draw_vertical_line(win, &ray, x);
		x++;
	}
	mlx_image_to_window(win->mlx, win->img, 0, 0);
}
