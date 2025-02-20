/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:48:09 by yaoberso          #+#    #+#             */
/*   Updated: 2025/02/19 13:18:00 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	condition_stop_tout(t_philosophe *philosophe)
{
	int	stop;

	stop = (philosophe->data->stop_tout == 1 || philosophe->data->is_dead == 1);
	return (stop);
}

void	action_routine(t_philosophe *philosophe)
{
	while (1)
	{
		lock_routine(philosophe);
		if (condition_stop_tout(philosophe))
		{
			pthread_mutex_unlock(&philosophe->data->death_mutex);
			pthread_mutex_unlock(&philosophe->data->stop_mutex);
			return ;
		}
		pthread_mutex_unlock(&philosophe->data->death_mutex);
		pthread_mutex_unlock(&philosophe->data->stop_mutex);
		penser(philosophe);
		prendre_fourchette(philosophe);
		if (!manger(philosophe))
			break ;
		pthread_mutex_lock(&philosophe->meal_mutex);
		if (philosophe->data->rep_min != -1
			&& philosophe->nb_meal >= philosophe->data->rep_min)
		{
			pthread_mutex_unlock(&philosophe->meal_mutex);
			return ;
		}
		pthread_mutex_unlock(&philosophe->meal_mutex);
		dormir(philosophe);
	}
}

void	*routine_philo(void *arg)
{
	t_philosophe	*philosophes;

	if (!arg)
		return (NULL);
	philosophes = (t_philosophe *)arg;
	if (!philosophes->data)
		return (NULL);
	pthread_mutex_lock(&philosophes->meal_mutex);
	philosophes->last_meal_time = get_time();
	pthread_mutex_unlock(&philosophes->meal_mutex);
	if (philosophes->id % 2 == 0 && philosophes->data->nb_philo > 1)
		usleep(100);
	action_routine(philosophes);
	return (NULL);
}
