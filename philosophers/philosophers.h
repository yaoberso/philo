/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:12:07 by yaoberso          #+#    #+#             */
/*   Updated: 2025/02/04 13:29:36 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef philosophers_H
#define philosophers_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include "printf/ft_printf.h"

typedef struct s_philosophe t_philosophe;

typedef struct s_philo
{
    int             nb_philo;
    int             temp_mort;
    int             temp_rep;
    int             temp_som;
    int             rep_min;
    long long       start_time;
    int             is_dead;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    pthread_mutex_t death_mutex; 
    t_philosophe    *philosophes;
}   t_philo;

typedef enum e_etat
{
    PENSER,
    MANGER,
    DORMIR
}   t_etat;

typedef struct s_philosophe
{
    int             id;
    int             dead;
    int             nb_meal;
    long long       last_meal_time;
    t_etat          etat;
    pthread_mutex_t mutex;
    pthread_t       thread;
    t_philo         *data;
}   t_philosophe;

int	ft_atoi(char *str);
void init_philo(t_philo *philo, char **argv);
void init_philosophes(t_philo *philo);
void routine_philo(t_philo *philo);
int check_death(t_philo *philo);
long long get_time(void);

#endif