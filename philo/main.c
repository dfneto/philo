/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:01:45 by davifern          #+#    #+#             */
/*   Updated: 2024/02/23 13:10:01 by davifern         ###   ########.fr       */
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
	gettimeofday(&fasting, NULL);

	usleep(3000);//simulacao para que now > fasting

	gettimeofday(&now, NULL);

	while (!philosopher_died(fasting, now, time_to_die))
	{
		gettimeofday(&now, NULL); //talvez possa remover as condições de morte e o gettimeofday daqui
		printf("%.5lu X has taken a fork\n", get_current_time(start, now));
		if (!philosopher_died(fasting, now, time_to_die)) //come
		{
			printf("%.5lu X is eating\n", get_current_time(start, now));
			usleep(time_to_eat * 1000);
			gettimeofday(&fasting, NULL); //começa o jejum
		}
		
		gettimeofday(&now, NULL);
		if (!philosopher_died(fasting, now, time_to_die)) //dorme
		{
			printf("%.5lu X is sleeping\n", get_current_time(start, now));
			usleep(time_to_sleep * 1000);
		}
		
		gettimeofday(&now, NULL);
		printf("%.5lu X is thinking\n", get_current_time(start, now)); //pensa
	}
	printf("%.5lu X died\n", get_current_time(start, now)); //morre

	return (0);
}
