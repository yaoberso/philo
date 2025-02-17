/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:48:09 by yaoberso          #+#    #+#             */
/*   Updated: 2025/02/17 11:43:22 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	action_routine(t_philosophe *philosophes)
{
	while (!check_death(philosophes))
	{
		penser(philosophes);
		if (check_death(philosophes))
			break ;
		prendre_fourchette(philosophes);
		if (!manger(philosophes))
			break ;
		if (philosophes->data->rep_min != -1
			&& check_all_meal(philosophes->data)
			&& philosophes->data->argc == 6)
			break ;
		if (check_death(philosophes))
			break ;
		if (philosophes->data->is_dead == 0)
			dormir(philosophes);
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
