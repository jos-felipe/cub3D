/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch2_player_management.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:00:00 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/07 10:30:40 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CH2_PLAYER_MANAGEMENT_H
# define CH2_PLAYER_MANAGEMENT_H

# include "MLX42/MLX42.h"
# include "ch0_scene_description_file.h"
# include "ch1_window_management.h"
# include "libft.h"

# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

void	init_player(t_player *player, t_map *map);
int		update_player_position(t_player *player, t_map *map, mlx_t *mlx);
int		check_collision(t_map *map, double new_x, double new_y);
void	rotate_player(t_player *player, double angle);

#endif