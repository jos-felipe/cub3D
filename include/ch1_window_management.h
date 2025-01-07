/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch1_window_management.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:14:38 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/07 16:17:09 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CH1_WINDOW_MANAGEMENT_H
# define CH1_WINDOW_MANAGEMENT_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include "ch0_scene_description_file.h"

# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 768
# define WINDOW_TITLE "cub3D"

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_mlx
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		*scene;
	t_player	player;
	int			width;
	int			height;
}				t_mlx;

int				init_window(t_mlx *win, t_scene *scene);
void			cleanup_window(t_mlx *win);
void			init_hooks(t_mlx *win);

#endif