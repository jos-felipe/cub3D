/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a4_ray_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:00:00 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/14 19:07:00 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch1_window_management.h"

static void	draw_textured_wall(t_mlx *win, t_ray *ray, int x)
{
	t_tex_calc	tc;
	t_texture	*texture;
	int			y;

	texture = select_wall_texture(&win->textures, ray);
	init_tex_calc(&tc, ray, &win->player);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		calculate_texture_y(&tc, y, ray->line_height);
		mlx_put_pixel(win->img, x, y,
			get_texture_color(texture, tc.tex_x, tc.tex_y));
		y++;
	}
}

void	draw_wall(t_mlx *win, t_ray *ray, int x)
{
	draw_textured_wall(win, ray, x);
}
