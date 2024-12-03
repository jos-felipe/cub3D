/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:53:31 by josfelip          #+#    #+#             */
/*   Updated: 2023/09/04 13:14:41 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(void *ptr)
{
	int	offset;

	offset = 0;
	if (!ptr)
	{
		offset += ft_putstr("(nil)");
		return (offset);
	}
	offset += ft_putstr("0x");
	offset += ft_puthex((unsigned long int)ptr, 0, 0);
	return (offset);
}

int	ft_parse(const char *str, va_list ap, int prefix_flag)
{
	int	offset;

	offset = 0;
	if (*str == 'c')
		offset = ft_putchar(va_arg(ap, int));
	else if (*str == 's')
		offset = ft_putstr(va_arg(ap, char *));
	else if (*str == 'd' || *str == 'i')
		offset = ft_putnbr(va_arg(ap, int), prefix_flag);
	else if (*str == 'u')
		offset = ft_putunbr(va_arg(ap, unsigned int));
	else if (*str == 'x')
		offset = ft_puthex(va_arg(ap, unsigned int), 0, prefix_flag);
	else if (*str == 'X')
		offset = ft_puthex(va_arg(ap, unsigned int), 1, prefix_flag);
	else if (*str == 'p')
		offset = ft_putptr(va_arg(ap, void *));
	else if (*str == '%')
		offset = ft_putchar('%');
	return (offset);
}

void	ft_prefix(const char *str, int *prefix_flag)
{
	if (*prefix_flag != '+')
		*prefix_flag = *str;
	else
		*prefix_flag = '+';
}

int	ft_printf(const char *str, ...)
{
	int		printed;
	int		prefix_flag;
	va_list	ap;

	if (!str)
		return (-1);
	va_start(ap, str);
	printed = 0;
	while (*str)
	{
		prefix_flag = 0;
		if (*str == '%')
		{
			str++;
			while (*str == '#' || *str == ' ' || *str == '+')
				ft_prefix(str++, &prefix_flag);
			printed += ft_parse(str, ap, prefix_flag);
		}
		else
			printed += ft_putchar(*str);
		str++;
	}
	va_end(ap);
	return (printed);
}
