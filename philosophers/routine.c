#include "philosophers.h"

void *routine_philo(void *arg)
{
    t_philosophe *philosophes;
    
    if (!arg)
        return (NULL);   
    philosophes = (t_philosophe *)arg;
    if (!philosophes->data)
        return (NULL);
    usleep(100 * (philosophes->id % 2));
    philosophes->last_meal_time = get_time();
    while (1)
    {
        if (check_death(philosophes))
            break;
        if (philosophes->data->rep_min != -1 && 
            philosophes->nb_meal >= philosophes->data->rep_min)
            break; 
        penser(philosophes);
        if (check_death(philosophes))
            break; 
        prendre_fourchette(philosophes);
        if (!manger(philosophes))
            break;   
        if (check_death(philosophes))
            break;   
        if (philosophes->data->rep_min == -1 || 
            philosophes->nb_meal < philosophes->data->rep_min)
        {
            dormir(philosophes);
        }
    }
    return (NULL);
}
