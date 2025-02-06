#include "philosophers.h"

void *routine_philo(void *arg)
{
    t_philosophe *philosophes;
    
    if (!arg)
        return (NULL);   
    philosophes = (t_philosophe *)arg;
    if (!philosophes->data)
        return (NULL);
        
    usleep(100);
    philosophes->last_meal_time = get_time();
    
    while (!philosophes->data->is_dead && 
           (philosophes->data->rep_min == -1 || 
            philosophes->nb_meal < philosophes->data->rep_min))
    {
        if (check_death(philosophes))
            break;
        penser(philosophes);
        prendre_fourchette(philosophes);
        if (!manger(philosophes))
            break;
        if (philosophes->data->rep_min == -1 || 
            philosophes->nb_meal < philosophes->data->rep_min)
        {
            dormir(philosophes);
        }
    }
    return (NULL);
}
