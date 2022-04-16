/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:46:08 by maxperei          #+#    #+#             */
/*   Updated: 2021/11/19 19:05:22 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *fmt, ...)
{
	int		len;
	va_list	ap;

	len = 0;
	va_start(ap, fmt);
	while (*fmt)
	{
		if (*fmt != '%')
		{
			ft_putchar(*fmt);
			len++;
		}
		else
		{
			len += ft_search_type(ap, fmt + 1);
			fmt++;
		}
		fmt++;
	}
	va_end(ap);
	return (len);
}
