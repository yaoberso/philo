/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:24:38 by yaoberso          #+#    #+#             */
/*   Updated: 2025/02/13 14:24:44 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void penser(t_philosophe *philosophes)
{
    if (!philosophes)
        return;
    pthread_mutex_lock(&philosophes->mutex);
    philosophes->etat = PENSER;
    pthread_mutex_unlock(&philosophes->mutex);
    print_message(philosophes, "is thinking");
}

int manger(t_philosophe *philosophes)
{
    const long long start_time = get_time();
    const long long end_time = start_time + philosophes->data->temp_rep;
    if (!philosophes || !philosophes->data)
        return (0);
    if (check_death(philosophes))
    {
        relacher_fourchette(philosophes);
        return (0);
    }
    pthread_mutex_lock(&philosophes->mutex);
    philosophes->etat = MANGER;
    pthread_mutex_unlock(&philosophes->mutex);
    print_message(philosophes, "is eating");
    pthread_mutex_lock(&philosophes->meal_mutex);
    philosophes->last_meal_time = start_time;
    pthread_mutex_unlock(&philosophes->meal_mutex);
    while (get_time() < (const long long)end_time)
    {
        if (check_death(philosophes))
        {
            relacher_fourchette(philosophes);
            return (0);
        }
        usleep(500);
    }

    pthread_mutex_lock(&philosophes->meal_mutex);
    philosophes->nb_meal++;
    pthread_mutex_unlock(&philosophes->meal_mutex);

    relacher_fourchette(philosophes);
    return (1);
}

void dormir(t_philosophe *philosophes)
{
    pthread_mutex_lock(&philosophes->mutex);
    philosophes->etat = DORMIR;
    pthread_mutex_unlock(&philosophes->mutex);
    
    print_message(philosophes, "is sleeping");
    usleep(philosophes->data->temp_som * 1000);
}

void relacher_fourchette(t_philosophe *philosophe)
{
    int gauche = philosophe->id;
    int droite = (philosophe->id + 1) % philosophe->data->nb_philo;

    if (philosophe->data->nb_philo > 1) 
    {
        pthread_mutex_unlock(&philosophe->data->forks[gauche]);
        pthread_mutex_unlock(&philosophe->data->forks[droite]);
    }
}


void prendre_fourchette(t_philosophe *philosophe)
{
    int gauche = philosophe->id;
    int droite = (philosophe->id + 1) % philosophe->data->nb_philo;

    if (check_death(philosophe))
        return;

    if (philosophe->data->nb_philo == 1)
    {
        print_message(philosophe, "has taken a fork");
        while (!check_death(philosophe))
            usleep(1000);
        return;
    }
    if (gauche < droite)
    {
        pthread_mutex_lock(&philosophe->data->forks[gauche]);
        print_message(philosophe, "has taken a fork");
        pthread_mutex_lock(&philosophe->data->forks[droite]);
        print_message(philosophe, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(&philosophe->data->forks[droite]);
        print_message(philosophe, "has taken a fork");
        pthread_mutex_lock(&philosophe->data->forks[gauche]);
        print_message(philosophe, "has taken a fork");
    }
}
