/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_lower.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:33:47 by yaoberso          #+#    #+#             */
/*   Updated: 2024/10/17 14:41:40 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_lower(unsigned int nb)
{
	int		count;
	char	*list_hex;

	count = 0;
	list_hex = "0123456789abcdef";
	if (nb >= 16)
	{
		count += ft_puthex_lower(nb / 16);
	}
	count += ft_putchar(list_hex[nb % 16]);
	return (count);
}
