/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:52:01 by yaoberso          #+#    #+#             */
/*   Updated: 2024/10/17 14:59:12 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putpointer(void *pointer)
{
	int				count;
	unsigned long	adresse;

	count = 0;
	if (pointer == NULL)
	{
		return (ft_putstr("0x0"));
	}
	adresse = (unsigned long)pointer;
	count += ft_putstr("0x");
	count += ft_puthex_lower(adresse);
	return (count);
}
