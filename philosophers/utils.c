#include "philosophers.h"

int	ft_atoi(char *str)
{
	int	i;
	int	r;
	int	s;

	i = 0;
	r = 0;
	s = 1;
	
	while(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			s = s * -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - 48);
		i++;
	}
	return (r * s);
}

long long get_time(void)
{
    struct timeval tv;
    long long time;

    gettimeofday(&tv, NULL);
    time = (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (time);
}

void print_message(t_philosophe *philosophe, char *message)
{
    pthread_mutex_lock(&philosophe->data->print_mutex);
    if (!check_death(philosophe))
        printf("%lld %d %s\n", (get_time() - philosophe->data->start_time), (philosophe->id + 1), message);
    pthread_mutex_unlock(&philosophe->data->print_mutex);
}