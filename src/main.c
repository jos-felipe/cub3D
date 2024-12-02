/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:11:26 by josfelip          #+#    #+#             */
/*   Updated: 2024/12/02 12:57:39 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../lib/libft/include/libft.h"
#include "../include/ch0_scene_description_file.h"

int	main(int argc, char *argv[])
{
	int		ret;
	t_scene	maze;
	
	ret = 0;
	if (argc != 2)
		return (write2err_and_return(ERROR_INVALID_ARGS, 1));
	ret = parse_scene(argv[1], &maze);
	free_heap(&maze);
	return (ret);
}
