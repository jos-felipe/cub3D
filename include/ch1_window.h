/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch1_window.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:14:38 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/02 13:14:42 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CH1_WINDOW_H
# define CH1_WINDOW_H

# include <MLX42/MLX42.h>
# include "ch0_scene_description_file.h"

# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 768
# define WINDOW_TITLE "cub3D"

typedef struct s_window
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		*scene;
}	t_window;

int		init_window(t_window *window, t_scene *scene);
void	game_loop(void *param);
void	handle_keys(mlx_key_data_t keydata, void *param);
void	clean_window(t_window *window);

#endif