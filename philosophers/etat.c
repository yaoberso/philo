#include "philosophers.h"

void penser(t_philosophe *philosophes)
{
	philosophes->etat = PENSER;
	print_message(philosophes, "is thinking");
}

int manger(t_philosophe *philosophes)
{
    if (check_death(philosophes))
    {
        relacher_fourchette(philosophes);
        return (0);
    }
    
    philosophes->etat = MANGER;
    print_message(philosophes, "is eating");
    pthread_mutex_lock(&philosophes->meal_mutex);
    philosophes->last_meal_time = get_time();
    pthread_mutex_unlock(&philosophes->meal_mutex);
    
    int time_slept = 0;
    while (time_slept < philosophes->data->temp_rep)
    {
        if (check_death(philosophes))
        {
            relacher_fourchette(philosophes);
            return (0);
        }
        usleep(1000);
        time_slept++;
    }
    
    philosophes->nb_meal++;
    relacher_fourchette(philosophes);
    return (1);
}

void dormir(t_philosophe *philosophes)
{
	philosophes->etat = DORMIR;
	print_message(philosophes, "is sleeping");
    usleep(philosophes->data->temp_som * 1000);
}

void relacher_fourchette(t_philosophe *philosophe)
{
    int gauche = philosophe->id;
    int droite = (philosophe->id + 1) % philosophe->data->nb_philo;

    pthread_mutex_unlock(&philosophe->data->forks[gauche]);
    pthread_mutex_unlock(&philosophe->data->forks[droite]);
}

void prendre_fourchette(t_philosophe *philosophe)
{
    int gauche = philosophe->id;
    int droite = (philosophe->id + 1) % philosophe->data->nb_philo;

    // Vérifie la mort avant chaque tentative de lock
    if (check_death(philosophe))
        return;

    if (gauche < droite)
    {
        pthread_mutex_lock(&philosophe->data->forks[gauche]);
        if (check_death(philosophe))
        {
            pthread_mutex_unlock(&philosophe->data->forks[gauche]);
            return;
        }
        print_message(philosophe, "has taken a fork");
        
        pthread_mutex_lock(&philosophe->data->forks[droite]);
        if (check_death(philosophe))
        {
            pthread_mutex_unlock(&philosophe->data->forks[gauche]);
            pthread_mutex_unlock(&philosophe->data->forks[droite]);
            return;
        }
        print_message(philosophe, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(&philosophe->data->forks[droite]);
        if (check_death(philosophe))
        {
            pthread_mutex_unlock(&philosophe->data->forks[droite]);
            return;
        }
        print_message(philosophe, "has taken a fork");
        
        pthread_mutex_lock(&philosophe->data->forks[gauche]);
        if (check_death(philosophe))
        {
            pthread_mutex_unlock(&philosophe->data->forks[droite]);
            pthread_mutex_unlock(&philosophe->data->forks[gauche]);
            return;
        }
        print_message(philosophe, "has taken a fork");
    }
}