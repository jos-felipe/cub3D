/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a1_ray_dda.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:30:00 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/09 11:30:00 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch2_ray_casting.h"

static void	perform_dda_step(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

static int	is_wall_hit(t_map *map, t_ray *ray)
{
	if (ray->map_x < 0 || ray->map_y < 0 || ray->map_x >= map->width
		|| ray->map_y >= map->height)
		return (1);
	return (map->grid[ray->map_y][ray->map_x] == '1');
}

void	perform_dda(t_ray *ray, t_map *map)
{
	while (!ray->hit)
	{
		perform_dda_step(ray);
		if (is_wall_hit(map, ray))
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

void	calculate_wall_height(t_ray *ray, int height)
{
	ray->line_height = (int)(height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + height / 2;
	if (ray->draw_end >= height)
		ray->draw_end = height - 1;
}
