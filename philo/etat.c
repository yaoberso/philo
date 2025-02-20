/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:24:38 by yaoberso          #+#    #+#             */
/*   Updated: 2025/02/19 13:12:22 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	penser(t_philosophe *philosophes)
{
	if (!philosophes)
		return ;
	pthread_mutex_lock(&philosophes->mutex);
	philosophes->etat = PENSER;
	pthread_mutex_unlock(&philosophes->mutex);
	if (!(check_death(philosophes)) || philosophes->data->is_dead == 0)
		print_message(philosophes, "is thinking");
}

int	manger(t_philosophe *philosophes)
{
	const long long	start_time = get_time();
	const long long	end_time = start_time + philosophes->data->temp_rep;

	if (!philosophes || !philosophes->data)
		return (0);
	if (check_death(philosophes))
	{
		relacher_fourchette(philosophes);
		return (0);
	}
	manger2(philosophes, start_time);
	while (get_time() < (const long long)end_time)
	{
		if (check_death(philosophes))
		{
			relacher_fourchette(philosophes);
			return (0);
		}
		usleep(500);
	}
	pthread_mutex_lock(&philosophes->meal_mutex);
	philosophes->nb_meal++;
	pthread_mutex_unlock(&philosophes->meal_mutex);
	relacher_fourchette(philosophes);
	return (1);
}

void	dormir(t_philosophe *philosophes)
{
	pthread_mutex_lock(&philosophes->mutex);
	philosophes->etat = DORMIR;
	pthread_mutex_unlock(&philosophes->mutex);
	if (!(check_death(philosophes)))
		print_message(philosophes, "is sleeping");
	usleep(philosophes->data->temp_som * 1000);
}

void	relacher_fourchette(t_philosophe *philosophe)
{
	int	gauche;
	int	droite;

	gauche = philosophe->id;
	droite = (philosophe->id + 1) % philosophe->data->nb_philo;
	if (philosophe->has_fork_left)
	{
		pthread_mutex_unlock(&philosophe->data->forks[gauche]);
		philosophe->has_fork_left = 0;
	}
	if (philosophe->has_fork_right && philosophe->data->nb_philo > 1)
	{
		pthread_mutex_unlock(&philosophe->data->forks[droite]);
		philosophe->has_fork_right = 0;
	}
}

void	prendre_fourchette(t_philosophe *philosophe)
{
	int	first_fork;
	int	second_fork;

	if (philosophe->id == philosophe->data->nb_philo - 1)
	{
		first_fork = (philosophe->id + 1) % philosophe->data->nb_philo;
		second_fork = philosophe->id;
	}
	else
	{
		first_fork = philosophe->id;
		second_fork = (philosophe->id + 1) % philosophe->data->nb_philo;
	}
	if (check_death(philosophe))
		return ;
	prendre_fourchette2(philosophe, first_fork, second_fork);
}
