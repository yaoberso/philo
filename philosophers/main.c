#include "philosophers.h"

int main(int argc, char **argv)
{
	t_philo *philo;

	philo = malloc(sizeof(t_philo));
	if (argc != 6)
		return (0);
	init_philo(philo, argv);
	init_philosophes(philo);
	init_thread(philo);
}
