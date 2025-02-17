/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:12:07 by yaoberso          #+#    #+#             */
/*   Updated: 2025/02/17 11:02:04 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_philosophe	t_philosophe;

typedef struct s_philo
{
	int						argc;
	int						nb_philo;
	int						temp_mort;
	int						temp_rep;
	int						temp_som;
	int						rep_min;
	long long				start_time;
	int						is_dead;
	pthread_mutex_t			*forks;
	pthread_mutex_t			print_mutex;
	pthread_mutex_t			death_mutex;
	t_philosophe			*philosophes;
}							t_philo;

typedef enum e_etat
{
	PENSER,
	MANGER,
	DORMIR,
}							t_etat;

typedef struct s_philosophe
{
	int						id;
	int						dead;
	int						nb_meal;
	long long				last_meal_time;
	t_etat					etat;
	pthread_mutex_t			mutex;
	pthread_mutex_t			meal_mutex;
	pthread_t				thread;
	t_philo					*data;
}							t_philosophe;

void						mutex_prendre_fourchette(t_philosophe *philosophe,
								int droite, int gauche);
void						manger2(t_philosophe *philosophes,
								long long start_time);
int							check_alph_and_neg(char **argv);
void						free_philo(t_philo *philo);
int							check_all_meal(t_philo *philo);
void						print_message(t_philosophe *philosophe,
								char *message);
void						init_thread(t_philo *philo);
void						prendre_fourchette(t_philosophe *philosophe);
void						relacher_fourchette(t_philosophe *philosophe);
void						dormir(t_philosophe *philosophes);
int							manger(t_philosophe *philosophes);
void						penser(t_philosophe *philosophes);
int							ft_atoi(char *str);
void						init_philo(t_philo *philo, char **argv, int argc);
void						init_philosophes(t_philo *philo);
void						*routine_philo(void *arg);
int							check_death(t_philosophe *philosophe);
long long					get_time(void);

#endif