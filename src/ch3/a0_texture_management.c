/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a0_texture_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:00:00 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/14 19:07:03 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ch3_textures.h"

t_texture	*load_texture(char *path)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		return (NULL);
	texture->data = mlx_load_png(path);
	if (!texture->data)
	{
		free(texture);
		return (NULL);
	}
	texture->width = texture->data->width;
	texture->height = texture->data->height;
	return (texture);
}

static int	load_wall_textures(t_mlx *win)
{
	win->textures.north = load_texture(win->scene->textures.north);
	if (!win->textures.north)
		return (1);
	win->textures.south = load_texture(win->scene->textures.south);
	if (!win->textures.south)
		return (1);
	win->textures.east = load_texture(win->scene->textures.east);
	if (!win->textures.east)
		return (1);
	win->textures.west = load_texture(win->scene->textures.west);
	if (!win->textures.west)
		return (1);
	return (0);
}

int	load_textures(t_mlx *win)
{
	ft_memset(&win->textures, 0, sizeof(t_wall_textures));
	if (load_wall_textures(win))
	{
		cleanup_textures(&win->textures);
		return (1);
	}
	return (0);
}

void	cleanup_textures(t_wall_textures *textures)
{
	if (textures->north)
	{
		mlx_delete_texture(textures->north->data);
		free(textures->north);
	}
	if (textures->south)
	{
		mlx_delete_texture(textures->south->data);
		free(textures->south);
	}
	if (textures->east)
	{
		mlx_delete_texture(textures->east->data);
		free(textures->east);
	}
	if (textures->west)
	{
		mlx_delete_texture(textures->west->data);
		free(textures->west);
	}
}
