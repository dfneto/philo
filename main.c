/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:01:45 by davifern          #+#    #+#             */
/*   Updated: 2024/02/19 14:07:19 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
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
	return (0);
}
