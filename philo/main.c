/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:01:45 by davifern          #+#    #+#             */
/*   Updated: 2024/02/23 11:05:58 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	struct timeval start;
	struct timeval time_now;

	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_times_eat;

	gettimeofday(&start, NULL);

	if (check_input(argc, argv))
		return (1);
	number_of_philosophers = ft_atoi(argv[1]);
	time_to_die = ft_atoi(argv[2]);
	time_to_eat = ft_atoi(argv[3]);
	time_to_sleep = ft_atoi(argv[4]);
	n_times_eat = 0;
	if (argv[5])
		n_times_eat = ft_atoi(argv[5]);
	

	printf("Number of philosophers: %d\n"
		"Time to die: %d\nTime to eat: %d\nTime to sleep: %d\n"
		"# times each philosopher must eat: %d\n", number_of_philosophers,
		time_to_die, time_to_eat, time_to_sleep, n_times_eat);
	
	
	while (tempo inicio - tempo atual < tempo de morte)
	{
		gettimeofday(&time_now, NULL);
		printf("%lu X has taken a fork\n", (time_now.tv_sec * 1000 + time_now.tv_usec/1000));
		
		gettimeofday(&time_now, NULL);
		printf("%lu X is eating\n", (time_now.tv_sec * 1000 + time_now.tv_usec/1000));
		usleep(time_to_eat * 1000);
		
		gettimeofday(&time_now, NULL);
		printf("%lu X is sleeping\n", (time_now.tv_sec * 1000 + time_now.tv_usec/1000));
		usleep(time_to_sleep * 1000);
		
		gettimeofday(&time_now, NULL);
		printf("%lu X is thinking\n", (time_now.tv_sec * 1000 + time_now.tv_usec/1000));
	}

	gettimeofday(&time_now, NULL);
	printf("%lu X died\n", (time_now.tv_sec * 1000 + time_now.tv_usec/1000));


	return (0);
}
