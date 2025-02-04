#include "philosophers.h"

void init_philo(t_philo *philo, char **argv)
{
	philo = malloc(sizeof(t_philo));
	if(!philo)
		return ;
	philo->nb_philo = ft_atoi(argv[1]);
	philo->temp_mort = ft_atoi(argv[2]);
	philo->temp_rep = ft_atoi(argv[3]);
	philo->temp_som = ft_atoi(argv[4]);
	philo->rep_min = ft_atoi(argv[5]);
	philo->philosophes = malloc(sizeof(t_philosophe) * philo->nb_philo);
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->nb_philo);
	if (!philo->philosophes || !philo->forks)
	{
    	printf("Erreur d'allocation mémoire\n");
    	free(philo->philosophes);
    	free(philo->forks);
    	free(philo);
    	return ;
	}
}

void init_philosophes(t_philo *philo)
{
	int i;

	i = 0;
	while(i < philo->nb_philo)
	{
		philo->philosophes[i].id = i;
    	philo->philosophes[i].nb_meal = 0;
    	philo->philosophes[i].last_meal_time = 0;
    	philo->philosophes[i].data = philo;
    	pthread_mutex_init(&philo->philosophes[i].mutex, NULL);
		i++;
	}
}

void init_thread(t_philo *philo)
{
	int i;

	i = 0;
	while(i < philo->nb_philo)
	{
		pthread_create(&philo->philosophes[i].thread, NULL, routine_philo, &philo->philosophes[i]);
		i++;
	}
}