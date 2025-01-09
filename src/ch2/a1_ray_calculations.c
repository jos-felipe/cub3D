/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a1_ray_calculations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:15:00 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/09 09:07:40 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch2_ray_casting.h"

void	calculate_ray_position(t_ray *ray, t_player *player, int x, int width)
{
	ray->camera_x = 2 * x / (double)width - 1;
	ray->dir_x = player->dir_x + (player->plane_x * ray->camera_x);
	ray->dir_y = player->dir_y + (player->plane_y * ray->camera_x);
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
}

static void	set_x_side_dist(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x)
			* ray->delta_dist_x;
	}
}

static void	set_y_side_dist(t_ray *ray, t_player *player)
{
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y)
			* ray->delta_dist_y;
	}
}

void	calculate_step_distance(t_ray *ray, t_player *player)
{
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
	set_x_side_dist(ray, player);
	set_y_side_dist(ray, player);
	ray->hit = 0;
}
