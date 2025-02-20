/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:47:22 by yaoberso          #+#    #+#             */
/*   Updated: 2025/02/19 13:03:49 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_monitoring(void *arg)
{
	t_philosophe	*philosophes;
	int				i;

	philosophes = (t_philosophe *)arg;
	if (!philosophes)
		return (NULL);
	while (1)
	{
		i = 0;
		while (i < philosophes->data->nb_philo)
		{
			if (check_death(&philosophes[i])
				|| check_all_meal(philosophes->data))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}
