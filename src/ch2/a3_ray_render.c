/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a3_ray_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:00:00 by expert42          #+#    #+#             */
/*   Updated: 2025/01/14 17:54:27 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch1_window_management.h"

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
	ft_memset(win->img->pixels, 0,
		win->width * win->height * sizeof(int32_t));
	cast_rays(win);
	mlx_image_to_window(win->mlx, win->img, 0, 0);
}
