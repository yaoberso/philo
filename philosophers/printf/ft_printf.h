/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:42:32 by yaoberso          #+#    #+#             */
/*   Updated: 2024/10/17 14:41:01 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>

int	ft_printf(const char *format, ...);
int	ft_putchar(char c);
int	ft_puthex_lower(unsigned int nb);
int	ft_puthex_upper(unsigned int nb);
int	ft_putnbr(long nb);
int	ft_putpointer(void *pointer);
int	ft_putstr(const char *str);
int	ft_putunsint(unsigned int nb);

#endif
