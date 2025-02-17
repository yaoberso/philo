/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:03:45 by yaoberso          #+#    #+#             */
/*   Updated: 2025/02/17 11:50:47 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	mutex_prendre_fourchette(t_philosophe *philosophe, int droite,
		int gauche)
{
	if (gauche < droite)
	{
		pthread_mutex_lock(&philosophe->data->forks[gauche]);
		if (!(check_death(philosophe)))
			print_message(philosophe, "has taken a fork");
		pthread_mutex_lock(&philosophe->data->forks[droite]);
		if (!(check_death(philosophe)))
			print_message(philosophe, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philosophe->data->forks[droite]);
		if (!(check_death(philosophe)))
			print_message(philosophe, "has taken a fork");
		pthread_mutex_lock(&philosophe->data->forks[gauche]);
		if (!(check_death(philosophe)))
			print_message(philosophe, "has taken a fork");
	}
}
