/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a4_ray_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:45:00 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/09 09:30:51 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch2_ray_casting.h"

static int	get_wall_color(t_ray *ray)
{
	int	color;

	if (ray->side == 1)
	{
		if (ray->dir_y > 0)
			color = 0xFF0000FF;
		else
			color = 0x00FF00FF;
	}
	else
	{
		if (ray->dir_x > 0)
			color = 0x0000FFFF;
		else
			color = 0xFFFF00FF;
	}
	if (ray->side == 1)
		color = (color >> 1) & 0x7F7F7FFF;
	return (color);
}

void	draw_wall(t_mlx *win, t_ray *ray, int x)
{
	int	y;
	int	color;

	color = get_wall_color(ray);
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		mlx_put_pixel(win->img, x, y, color);
		y++;
	}
}
