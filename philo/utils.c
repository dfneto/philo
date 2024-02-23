/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:01:07 by davifern          #+#    #+#             */
/*   Updated: 2024/02/23 11:43:33 by davifern         ###   ########.fr       */
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

/*
* Returns the elapsed time since the program starts
*/
unsigned long	get_current_time(struct timeval start, struct timeval now)
{
	return ((unsigned long)(now.tv_sec * 1000 + now.tv_usec / 1000)
		- (start.tv_sec * 1000 + start.tv_usec / 1000));
}
