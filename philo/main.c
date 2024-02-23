/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:01:45 by davifern          #+#    #+#             */
/*   Updated: 2024/02/23 11:41:05 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	main(int argc, char **argv)
{
	struct timeval start;
	struct timeval now;
	struct timeval fasting;

	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_times_eat;

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
	
	gettimeofday(&start, NULL);

	// while (tempo sem comer - tempo atual < tempo de morte)
	// {
		gettimeofday(&now, NULL);
		printf("%.5lu X has taken a fork\n", get_current_time(start, now));
		
		gettimeofday(&now, NULL);
		printf("%.5lu X is eating\n", get_current_time(start, now));
		usleep(time_to_eat * 1000);
		gettimeofday(&fasting, NULL); //começa o jejum
		
		gettimeofday(&now, NULL);
		printf("%.5lu X is sleeping\n", get_current_time(start, now));
		usleep(time_to_sleep * 1000);
		
		gettimeofday(&now, NULL);
		printf("%.5lu X is thinking\n", get_current_time(start, now));
	// }

	// gettimeofday(&now, NULL);
	// printf("%lu X died\n", (now.tv_sec * 1000 + now.tv_usec/1000));


	return (0);
}
