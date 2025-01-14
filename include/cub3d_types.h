/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:24:44 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/14 19:11:33 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_TYPES_H
# define CUB3D_TYPES_H

# include "MLX42/MLX42.h"

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_textures;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;

typedef struct s_scene
{
	t_textures	textures;
	t_color		floor;
	t_color		ceiling;
	t_map		map;
}	t_scene;

typedef enum e_error
{
	INVALID_ARGS = 1,
	INVALID_FILE_EXT,
	INVALID_FD,
	INVALID_MAP,
	INVALID_TEXTURE,
	INVALID_COLOR,
	INVALID_PLAYER,
	INVALID_MAP_CHARS,
	INVALID_MALLOC,
	INVALID_IDENTIFIER,
	UNDEFINED_ERROR
}	t_error;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

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

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_mlx
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_scene			*scene;
	t_player		player;
	t_wall_textures	textures;
	int				width;
	int				height;
}				t_mlx;

#endif