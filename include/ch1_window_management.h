/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch1_window_management.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:00:00 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/21 16:24:47 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CH1_WINDOW_MANAGEMENT_H
# define CH1_WINDOW_MANAGEMENT_H

# include <math.h>
# include "MLX42/MLX42.h"
# include "libft.h"
# include "cub3d_types.h"
# include "ch2_ray_casting.h"
# include "ch3_textures.h"

# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 768
# define WINDOW_TITLE "cub3D"
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03
# define FRAME_RATE 60

int		check_collision(t_map *map, double new_x, double new_y);
int		init_window(t_mlx *win, t_scene *scene);
int		update_player_position(t_player *player, t_map *map, mlx_t *mlx);
void	cleanup_window(t_mlx *win);
void	init_hooks(t_mlx *win);
void	init_player(t_player *player, t_map *map);
void	initialize_rendering(t_mlx *win);
void	rotate_player(t_player *player, double angle);
void	render_frame(t_mlx *win);

#endif