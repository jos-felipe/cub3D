/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_textures.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: expert42 <expert42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:00:00 by expert42          #+#    #+#             */
/*   Updated: 2025/01/14 10:00:00 by expert42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_TEXTURES_H
# define CUB3D_TEXTURES_H

# include "MLX42/MLX42.h"
# include "ch0_scene_description_file.h"

# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

typedef struct s_texture
{
	mlx_texture_t	*data;
	int				width;
	int				height;
}	t_texture;

typedef struct s_tex_calc
{
	double			wall_x;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
}	t_tex_calc;

typedef struct s_wall_textures
{
	t_texture	*north;
	t_texture	*south;
	t_texture	*east;
	t_texture	*west;
}	t_wall_textures;

/* Texture management functions */
int			load_textures(t_mlx *win);
void		cleanup_textures(t_wall_textures *textures);
t_texture	*load_texture(mlx_t *mlx, char *path);
uint32_t	get_texture_color(t_texture *tex, int x, int y);

/* Texture calculation functions */
void		init_tex_calc(t_tex_calc *tc, t_ray *ray, t_player *player);
void		calculate_texture_y(t_tex_calc *tc, int y, int line_height);
t_texture	*select_wall_texture(t_wall_textures *textures, t_ray *ray);

#endif