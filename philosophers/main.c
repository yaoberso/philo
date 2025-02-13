#include "philosophers.h"

int main(int argc, char **argv)
{
	t_philo *philo;

	philo = malloc(sizeof(t_philo));
	if (argc != 6 && argc != 5)
		return (0);
	if (!check_alph_and_neg(argv))
	{
		free(philo);
		return (1);
	}
	init_philo(philo, argv, argc);
	init_philosophes(philo);
	init_thread(philo);
	free_philo(philo);
}
