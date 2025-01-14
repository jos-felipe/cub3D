/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a1_texture_calculations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:00:00 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/14 19:07:06 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch3_textures.h"

void	init_tex_calc(t_tex_calc *tc, t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		tc->wall_x = player->pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		tc->wall_x = player->pos_x + ray->perp_wall_dist * ray->dir_x;
	tc->wall_x -= floor(tc->wall_x);
	tc->tex_x = (int)(tc->wall_x * TEXTURE_WIDTH);
	if (ray->side == 0 && ray->dir_x < 0)
		tc->tex_x = TEXTURE_WIDTH - tc->tex_x - 1;
	if (ray->side == 1 && ray->dir_y > 0)
		tc->tex_x = TEXTURE_WIDTH - tc->tex_x - 1;
}

void	calculate_texture_y(t_tex_calc *tc, int y, int line_height)
{
	tc->step = 1.0 * TEXTURE_HEIGHT / line_height;
	tc->tex_pos = (y - WINDOW_HEIGHT / 2 + line_height / 2) * tc->step;
	tc->tex_y = (int)tc->tex_pos & (TEXTURE_HEIGHT - 1);
}

t_texture	*select_wall_texture(t_wall_textures *textures, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (textures->east);
		return (textures->west);
	}
	else
	{
		if (ray->dir_y > 0)
			return (textures->south);
		return (textures->north);
	}
}

uint32_t	get_texture_color(t_texture *tex, int x, int y)
{
	uint8_t		*pixel;
	uint32_t	color;

	pixel = tex->data->pixels + (y * tex->data->width + x) * 4;
	color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
	return (color);
}
