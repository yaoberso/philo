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

int check_all_meal(t_philo *philo)
{
    int i;
    int all_finished = 1;

    if (philo->rep_min == -1)
        return (0);

    pthread_mutex_lock(&philo->death_mutex);
    i = 0;
    while(i < philo->nb_philo)
    {
        pthread_mutex_lock(&philo->philosophes[i].meal_mutex);
        if(philo->philosophes[i].nb_meal < philo->rep_min)
        {
            all_finished = 0;
            pthread_mutex_unlock(&philo->philosophes[i].meal_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->philosophes[i].meal_mutex);
        i++;
    }
    pthread_mutex_unlock(&philo->death_mutex);
    
    return all_finished;
}