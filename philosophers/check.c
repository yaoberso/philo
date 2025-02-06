#include "philosophers.h"

int check_death(t_philosophe *philosophe)
{
	pthread_mutex_lock(&philosophe->data->death_mutex);
    if (philosophe->data->is_dead)
    {
        pthread_mutex_unlock(&philosophe->data->death_mutex);
        return (1);
    }
    
    long long current_time = get_time();
    pthread_mutex_lock(&philosophe->meal_mutex);
    if (current_time - philosophe->last_meal_time > philosophe->data->temp_mort)
    {
        philosophe->data->is_dead = 1;
        pthread_mutex_unlock(&philosophe->meal_mutex);
        pthread_mutex_unlock(&philosophe->data->death_mutex);
		print_message(philosophe, "is dead");
        return (1);
    }
    pthread_mutex_unlock(&philosophe->meal_mutex);
    pthread_mutex_unlock(&philosophe->data->death_mutex);
    return (0);
}
