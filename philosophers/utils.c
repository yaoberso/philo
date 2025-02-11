#include "philosophers.h"

int	ft_atoi(char *str)
{
	int	i;
	int	r;
	int	s;

	i = 0;
	r = 0;
	s = 1;
	
	while(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			s = s * -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - 48);
		i++;
	}
	return (r * s);
}

long long get_time(void)
{
    struct timeval tv;
    long long time;

    gettimeofday(&tv, NULL);
    time = (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (time);
}

void print_message(t_philosophe *philosophe, char *message)
{
    int should_print = 0;
    
    pthread_mutex_lock(&philosophe->data->death_mutex);
    should_print = !philosophe->data->is_dead;
    pthread_mutex_unlock(&philosophe->data->death_mutex);
    
    if (should_print)
    {
        pthread_mutex_lock(&philosophe->data->print_mutex);
        printf("%lld %d %s\n", (get_time() - philosophe->data->start_time), 
               (philosophe->id + 1), message);
        pthread_mutex_unlock(&philosophe->data->print_mutex);
    }
}

void free_philo(t_philo *philo)
{
    int i;

    if (!philo)
        return;

    i = 0;
    while (i < philo->nb_philo)
    {
        pthread_mutex_destroy(&philo->forks[i]);
        i++;
    }

    pthread_mutex_destroy(&philo->print_mutex);
    pthread_mutex_destroy(&philo->death_mutex);
    
    free(philo->forks);
    free(philo->philosophes);
    free(philo);
}
