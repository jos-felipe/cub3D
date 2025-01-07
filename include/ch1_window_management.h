/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch1_window_management.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:14:38 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/07 09:39:39 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CH1_WINDOW_MANAGEMENT_H
# define CH1_WINDOW_MANAGEMENT_H

# include "MLX42/MLX42.h"
# include "ch0_scene_description_file.h"
# include "libft.h"

# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 768
# define WINDOW_TITLE "cub3D"

typedef struct s_mlx
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		*scene;
	int			win_width;
	int			win_height;
}				t_mlx;

int				init_window(t_mlx *win, t_scene *scene);
void			cleanup_window(t_mlx *win);
void			init_hooks(t_mlx *win);

#endif