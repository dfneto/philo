/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:01:07 by davifern          #+#    #+#             */
/*   Updated: 2024/02/27 11:00:45 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* A simplified version of atoi*/
//TODO: if (result > 2147483647)?
int	ft_atoi(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return ((int)result);
}

int	check_input(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		printf("You have to pass 4 ou 5 args: number_of_philosophers, "
			"time_to_die, time_to_eat, time_to_sleep (all times in miliseconds)"
			"and optionally number_of_times_each_philosopher_must_eat\n");
		return (1);
	}
	argv++;
	while (*argv)
	{
		while ((*argv)[i])
		{
			if ((*argv)[i] < 48 || (*argv)[i] > 57)
				return (printf("The params must be positive integers\n"), 1);
			i++;
		}
		i = 0;
		argv++;
	}
	return (0);
}

t_god	*create_god(char **argv)
{
	t_god	*god;
	
	god = (t_god *)malloc(sizeof(t_god));
	if (!god)
		return (NULL);
	god->all_alive = 1;
	god->start = get_start_time();
	god->n_philo = ft_atoi(argv[1]);
	god->time_to_die = ft_atoi(argv[2]);
	god->time_to_eat = ft_atoi(argv[3]);
	god->time_to_sleep = ft_atoi(argv[4]);
	god->n_times_eat = 0;
	if (argv[5])
		god->n_times_eat = ft_atoi(argv[5]);
	god->philo = (t_philo *)malloc(sizeof(t_philo) * god->n_philo);
	if (!god->philo)
		return (NULL);
	return (god);
}

/*
* Returns the elapsed time since the program starts
*/
unsigned long	get_current_time(struct timeval start, struct timeval now)
{
	return ((unsigned long)(now.tv_sec * 1000 + now.tv_usec / 1000)
		- (start.tv_sec * 1000 + start.tv_usec / 1000));
}

/*
* Return the diference between the time now and the startime
*/
long long	get_time(long long start)
{
	long long		time_now;
	struct timeval	now;

	gettimeofday(&now, NULL);
	time_now = now.tv_sec * 1000 + now.tv_usec / 1000;
	// printf("Start time: %lld, Now: %lld, time_now - start: %lld\n", start, time_now, (time_now - start));
	return (time_now - start);
}

long long	get_start_time(void)
{
	long long		time_now;
	struct timeval	now;

	gettimeofday(&now, NULL);
	time_now = now.tv_sec * 1000 + now.tv_usec / 1000;
	// printf("Start time: %lld\n", time_now);
	return (time_now);
}

long long get_time_diff(long long start, long long now)
{
	return (now - start);
}

// long long	get_time(void)
// {
// 	struct timeval	now;

// 	gettimeofday(&now, NULL);
// 	return (now.tv_sec * 1000 + now.tv_usec / 1000);
// }

/*
* Returns:
*	1 - if the philosphy died
*	0 - if the philosphy DOESN'T died
*/
int	philosopher_died(t_philo *philo)
{
	long long		time_now;

	time_now = get_time(philo->god->start);
	if (time_now - philo->fasting > philo->god->time_to_die)
		return (1);
	return (0);
}

int	all_alived(t_philo *philo)
{
	if(!philosopher_died(philo) && philo->god->all_alive == 1)
		return (1);
	return (0);
}

void	philosopher_die(t_philo *philo)
{
	printf("%.5lld %d died\n", get_time(philo->god->start), philo->id); //morre
	philo->god->all_alive = 0;
}