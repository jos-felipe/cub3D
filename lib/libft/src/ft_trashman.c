/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trashman.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:44:33 by gfantoni          #+#    #+#             */
/*   Updated: 2024/06/26 13:53:25 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static t_list	**ft_get_mem_address(void);

void	ft_collect_mem(void *content)
{
	ft_lstadd_back(ft_get_mem_address(), ft_lstnew(content));
}

void	ft_free_trashman(void)
{
	t_list **lst_memory;
	t_list	*next;

	lst_memory = ft_get_mem_address();
	while (*lst_memory)
	{
		next = (*lst_memory)->next;
		free((*lst_memory)->content);
		free(*lst_memory);
		*lst_memory = next;
	}
	*lst_memory = NULL;
}

static t_list	**ft_get_mem_address(void)
{
	static t_list	*ptr;

	return (&ptr);
}
