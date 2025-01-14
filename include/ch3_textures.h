/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch3_textures.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:00:00 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/14 19:06:25 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CH3_TEXTURES_H
# define CH3_TEXTURES_H

# include <stdlib.h>
# include <math.h>
# include "../lib/libft/include/libft.h"
# include "cub3d_types.h"
# include "ch1_window_management.h"

# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

/* Texture management functions */
int			load_textures(t_mlx *win);
void		cleanup_textures(t_wall_textures *textures);
t_texture	*load_texture(char *path);
uint32_t	get_texture_color(t_texture *tex, int x, int y);

/* Texture calculation functions */
void		init_tex_calc(t_tex_calc *tc, t_ray *ray, t_player *player);
void		calculate_texture_y(t_tex_calc *tc, int y, int line_height);
t_texture	*select_wall_texture(t_wall_textures *textures, t_ray *ray);

#endif