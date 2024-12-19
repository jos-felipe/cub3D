/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:11:26 by josfelip          #+#    #+#             */
/*   Updated: 2024/12/18 09:35:02 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ch0_scene_description_file.h"
#include "libft.h"

int	main(int argc, char *argv[])
{
	int		ret;
	t_scene	maze;

	if (argc != 2)
		return (write2err_and_return(INVALID_ARGS));
	ret = parse_scene(argv[1], &maze);
	write2err(ret, &maze);
	free_scene(&maze);
	return (ret);
}
