#include "philosophers.h"

void *routine_philo(void *arg)
{
    t_philosophe *philosophes;
    
    if (!arg)
        return (NULL);   
    philosophes = (t_philosophe *)arg;
    if (!philosophes->data)
        return (NULL);
    if (philosophes->id % 2 == 0)
        usleep(philosophes->data->temp_rep * 100);
    philosophes->last_meal_time = get_time();
    while (1)
    {
        if (check_death(philosophes))
            break;
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
        dormir(philosophes);
    }
    return (NULL);
}
