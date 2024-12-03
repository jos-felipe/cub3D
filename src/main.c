/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:11:26 by josfelip          #+#    #+#             */
/*   Updated: 2024/12/03 00:14:47 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../lib/libft/include/libft.h"
#include "../include/ch0_scene_description_file.h"

int	main(int argc, char *argv[])
{
	int		ret;
	t_scene	maze;
	
	if (argc != 2)
		return (write2err_and_return(INVALID_ARGS));
	ret = parse_scene(argv[1], &maze);
	write2err(ret);
	free_scene(&maze);
	return (ret);
}
