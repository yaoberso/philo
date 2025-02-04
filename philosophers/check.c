#include "philosophers.h"

int check_death(t_philo *philo)
{
	int i;
	long long current_time;

	current_time = get_time();
	i = 0;
	while(i < philo->nb_philo)
	{
		pthread_mutex_lock(&philo->death_mutex);
		if (current_time - philo->philosophes[i].last_meal_time > philo->temp_mort)
		{
			philo->philosophes[i].dead = 1;
			pthread_mutex_unlock(&philo->death_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->death_mutex);
		i++;
	}
	return (0);
}