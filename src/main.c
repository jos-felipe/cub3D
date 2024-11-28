/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:11:26 by josfelip          #+#    #+#             */
/*   Updated: 2024/11/28 14:30:26 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../lib/libft/include/libft.h"
#include "../include/ch0_scene_description_file.h"

#define ERROR_INVALID_ARGS "Error\nInvalid arguments. Try: ./cub3D with a map in format *.cub\n"

int	main(int argc, char *argv[])
{
	t_scene	maze;
	
	if (argc != 2)
		return (write(2, ERROR_INVALID_ARGS, ft_strlen(ERROR_INVALID_ARGS)));
	parse_scene(argv[1], &maze);
	return (0);
}