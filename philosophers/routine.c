#include "philosophers.h"

void *routine_philo(void *arg)
{
    t_philosophe *philosophes;
    
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
    while (!check_death(philosophes))
    {
        penser(philosophes);
        if (check_death(philosophes))
            break;
        prendre_fourchette(philosophes);
        if (!manger(philosophes))
            break; 
        if (philosophes->data->rep_min != -1 && check_all_meal(philosophes->data) && philosophes->data->argc == 6)
            break;   
        if (check_death(philosophes))
            break;
        if (philosophes->data->is_dead == 0)
            dormir(philosophes);
    }
    return (NULL);
}
