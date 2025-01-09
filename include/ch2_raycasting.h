/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch2_ray_casting.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:00:00 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/09 10:00:00 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CH2_RAY_CASTING_H
# define CH2_RAY_CASTING_H

# include "ch1_window_management.h"

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

/* Core ray-casting functions */
void	cast_rays(t_mlx *win);
void	calculate_ray_position(t_ray *ray, t_player *player, int x, int width);
void	calculate_step_distance(t_ray *ray, t_player *player);
void	perform_dda(t_ray *ray, t_map *map);
void	calculate_wall_height(t_ray *ray, int height);

/* Rendering functions */
void	draw_vertical_line(t_mlx *win, t_ray *ray, int x);
void	render_frame(t_mlx *win);

#endif