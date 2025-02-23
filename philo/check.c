/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:24:24 by yaoberso          #+#    #+#             */
/*   Updated: 2025/02/19 11:44:01 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philosophe *philosophe)
{
	long long	current_time;

	pthread_mutex_lock(&philosophe->data->death_mutex);
	if (philosophe->data->is_dead)
	{
		pthread_mutex_unlock(&philosophe->data->death_mutex);
		return (1);
	}
	current_time = get_time();
	pthread_mutex_lock(&philosophe->meal_mutex);
	if (current_time - philosophe->last_meal_time > philosophe->data->temp_mort)
	{
		philosophe->data->is_dead = 1;
		pthread_mutex_unlock(&philosophe->meal_mutex);
		pthread_mutex_unlock(&philosophe->data->death_mutex);
		pthread_mutex_lock(&philosophe->data->print_mutex);
		printf("%lld %d %s\n", (get_time() - philosophe->data->start_time),
			(philosophe->id + 1), "is dead");
		pthread_mutex_unlock(&philosophe->data->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philosophe->meal_mutex);
	pthread_mutex_unlock(&philosophe->data->death_mutex);
	return (0);
}

int	check_all_meal(t_philo *philo)
{
	int	i;
	int	philo_fini;

	if (philo->rep_min == -1)
		return (0);
	i = 0;
	philo_fini = 0;
	pthread_mutex_lock(&philo->death_mutex);
	while (i < philo->nb_philo)
	{
		pthread_mutex_lock(&philo->philosophes[i].meal_mutex);
		if (philo->philosophes[i].nb_meal >= philo->rep_min)
			philo_fini++;
		pthread_mutex_unlock(&philo->philosophes[i].meal_mutex);
		i++;
	}
	pthread_mutex_unlock(&philo->death_mutex);
	if (philo_fini == philo->nb_philo)
	{
		pthread_mutex_lock(&philo->stop_mutex);
		philo->stop_tout = 1;
		pthread_mutex_unlock(&philo->stop_mutex);
		return (1);
	}
	return (0);
}

int	check_alph_and_neg(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (argv[i][j] == '+')
			j++;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Error\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
