/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch2_ray_casting.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:00:00 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/14 17:35:43 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CH2_RAY_CASTING_H
# define CH2_RAY_CASTING_H

# include "cub3d_types.h"

/* Core ray-casting functions */
void	cast_rays(t_mlx *win);
void	calculate_ray_position(t_ray *ray, t_player *player, int x, int width);
void	calculate_step_distance(t_ray *ray, t_player *player);
void	perform_dda(t_ray *ray, t_map *map);
void	calculate_wall_height(t_ray *ray, int height);

/* Rendering functions */
void	draw_vertical_line(t_mlx *win, t_ray *ray, int x);
void	draw_wall(t_mlx *win, t_ray *ray, int x);
void	render_frame(t_mlx *win);

#endif