#include "philosophers.h"

void penser(t_philo *philo)
{
	philo->philosophes.etat = PENSER;
}

void manger(t_philo *philo)
{
	
}

void dormir(t_philo *philo)
{
	
}

void routine_philo(t_philo *philo)
{
	while(1)
	{
		if (!check_death(philo))
		{
			break;
		}
	}
	penser
}