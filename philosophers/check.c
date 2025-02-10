#include "philosophers.h"

// int check_death(t_philosophe *philosophe)
// {
// 	pthread_mutex_lock(&philosophe->data->death_mutex);
//     if (philosophe->data->is_dead)
//     {
//         print_message(philosophe, "is dead");
//         pthread_mutex_unlock(&philosophe->data->death_mutex);
//         return (1);
//     }
    
//     long long current_time = get_time();
//     pthread_mutex_lock(&philosophe->meal_mutex);
//     if (current_time - philosophe->last_meal_time > philosophe->data->temp_mort)
//     {
//         philosophe->data->is_dead = 1;
//         pthread_mutex_unlock(&philosophe->meal_mutex);
//         pthread_mutex_unlock(&philosophe->data->death_mutex);
// 		print_message(philosophe, "is dead");
//         return (1);
//     }
//     pthread_mutex_unlock(&philosophe->meal_mutex);
//     pthread_mutex_unlock(&philosophe->data->death_mutex);
//     return (0);
// }

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
        
        // On prend le mutex d'impression pour être sûr d'afficher le message de mort
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
