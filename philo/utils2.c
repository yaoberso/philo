/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:03:45 by yaoberso          #+#    #+#             */
/*   Updated: 2025/02/19 13:18:10 by yaoberso         ###   ########.fr       */
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

void	prendre_fourchette2(t_philosophe *philosophe, int first_fork,
		int second_fork)
{
	if (philosophe->data->nb_philo == 1)
	{
		pthread_mutex_lock(&philosophe->data->forks[first_fork]);
		philosophe->has_fork_left = 1;
		if (!(check_death(philosophe)))
			print_message(philosophe, "has taken a fork");
		while (!check_death(philosophe))
			usleep(1000);
		return ;
	}
	pthread_mutex_lock(&philosophe->data->forks[first_fork]);
	if (first_fork == philosophe->id)
		philosophe->has_fork_left = 1;
	else
		philosophe->has_fork_right = 1;
	if (!(check_death(philosophe)))
		print_message(philosophe, "has taken a fork");
	pthread_mutex_lock(&philosophe->data->forks[second_fork]);
	if (second_fork == philosophe->id)
		philosophe->has_fork_left = 1;
	else
		philosophe->has_fork_right = 1;
	if (!(check_death(philosophe)))
		print_message(philosophe, "has taken a fork");
}

void	lock_routine(t_philosophe *philosophe)
{
	pthread_mutex_lock(&philosophe->data->stop_mutex);
	pthread_mutex_lock(&philosophe->data->death_mutex);
}
