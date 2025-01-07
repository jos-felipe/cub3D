/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:11:26 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/02 16:24:43 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch0_scene_description_file.h"
#include "ch1_window_management.h"
#include "libft.h"

int	main(int argc, char *argv[])
{
	int		ret;
	t_scene	maze;
	t_mlx	win;

	if (argc != 2)
		return (write2err_and_return(INVALID_ARGS));
	ret = parse_scene(argv[1], &maze);
	if (ret != 0)
	{
		write2err(ret, &maze);
		free_scene(&maze);
		return (ret);
	}
	if (init_window(&win, &maze) != 0)
	{
		free_scene(&maze);
		return (1);
	}
	mlx_loop(win.mlx);
	cleanup_window(&win);
	free_scene(&maze);
	return (0);
}
