/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:24:49 by yaoberso          #+#    #+#             */
/*   Updated: 2025/02/19 13:02:23 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo(t_philo *philo, char **argv, int argc)
{
	if (!philo)
		return ;
	philo->rep_min = -1;
	philo->argc = argc;
	philo->nb_philo = ft_atoi(argv[1]);
	philo->temp_mort = ft_atoi(argv[2]);
	philo->temp_rep = ft_atoi(argv[3]);
	philo->temp_som = ft_atoi(argv[4]);
	if (argc == 6)
		philo->rep_min = ft_atoi(argv[5]);
	philo->start_time = get_time();
	philo->is_dead = 0;
	philo->stop_tout = 0;
	philo->philosophes = malloc(sizeof(t_philosophe) * philo->nb_philo);
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->nb_philo);
	if (!philo->philosophes || !philo->forks)
	{
		printf("Erreur d'allocation mémoire\n");
		free(philo->philosophes);
		free(philo->forks);
		return ;
	}
	pthread_mutex_init(&philo->print_mutex, NULL);
	pthread_mutex_init(&philo->death_mutex, NULL);
	pthread_mutex_init(&philo->stop_mutex, NULL);
}

void	init_philosophes(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < philo->nb_philo)
	{
		philo->philosophes[i].id = i;
		philo->philosophes[i].nb_meal = 0;
		philo->philosophes[i].last_meal_time = get_time();
		philo->philosophes[i].data = philo;
		philo->philosophes[i].has_fork_right = 0;
		philo->philosophes[i].has_fork_left = 0;
		pthread_mutex_init(&philo->philosophes[i].mutex, NULL);
		pthread_mutex_init(&philo->philosophes[i].meal_mutex, NULL);
		i++;
	}
}

void	init_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		pthread_create(&philo->philosophes[i].thread, NULL, routine_philo,
			(void *)&philo->philosophes[i]);
		usleep(100);
		i++;
	}
	pthread_create(&philo->monitor, NULL, check_monitoring, philo->philosophes);
	i = 0;
	while (i < philo->nb_philo)
	{
		pthread_join(philo->philosophes[i].thread, NULL);
		i++;
	}
	pthread_join(philo->monitor, NULL);
}
