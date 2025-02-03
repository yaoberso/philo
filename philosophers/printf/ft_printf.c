/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:03:19 by yaoberso          #+#    #+#             */
/*   Updated: 2024/10/17 14:53:20 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_format(char format, va_list ap)
{
	if (format == 'c')
		return (ft_putchar(va_arg(ap, int)));
	else if (format == 's')
		return (ft_putstr(va_arg(ap, char *)));
	else if (format == 'p')
		return (ft_putpointer(va_arg(ap, void *)));
	else if (format == 'd')
		return (ft_putnbr(va_arg(ap, int)));
	else if (format == 'i')
		return (ft_putnbr(va_arg(ap, int)));
	else if (format == 'u')
		return (ft_putunsint(va_arg(ap, unsigned int)));
	else if (format == 'x')
		return (ft_puthex_lower(va_arg(ap, unsigned int)));
	else if (format == 'X')
		return (ft_puthex_upper(va_arg(ap, unsigned int)));
	else if (format == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		nb_char;
	int		i;

	va_start(ap, format);
	nb_char = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			nb_char += check_format(format[i + 1], ap);
			i += 2;
			continue ;
		}
		nb_char += ft_putchar(format[i]);
		i++;
	}
	va_end(ap);
	return (nb_char);
}
