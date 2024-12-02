/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:11:26 by josfelip          #+#    #+#             */
/*   Updated: 2024/12/02 10:25:49 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../lib/libft/include/libft.h"
#include "../include/ch0_scene_description_file.h"

int	main(int argc, char *argv[])
{
	t_scene	maze;
	
	if (argc != 2)
		return (write(2, ERROR_INVALID_ARGS, ft_strlen(ERROR_INVALID_ARGS)));
	parse_scene(argv[1], &maze);
	free_heap(&maze);
	return (0);
}
