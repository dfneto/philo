/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:39:15 by davifern          #+#    #+#             */
/*   Updated: 2024/03/06 13:49:56 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* A simplified version of atoi*/
static int	ft_atoi(const char *str)
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

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	print_params_error(void)
{
	printf("You have to pass 4 ou 5 args: number_of_philosophers, "
		"time_to_die, time_to_eat, time_to_sleep (all times in miliseconds)"
		"and optionally number_of_times_each_philosopher_must_eat\n");
	return (1);
}

int	check_input(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (print_params_error());
	if (ft_atoi(argv[1]) > 4000)
		return (printf("Maximum philosophers (4000) exceeded\n"), 1);
	if (argv[5] && ft_atoi(argv[5]) == 0)
		return (printf("If you want to set the number of times "
				"that a philo needs to eat it must be more than 0.\n"), 1);
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
		if (ft_strlen(*argv) > 9)
			return (printf("Number too big\n"), 1);
		argv++;
	}
	return (0);
}

void	get_input_data(char **argv, t_god *god)
{
	god->start = 0;
	god->n_philo = ft_atoi(argv[1]);
	god->time_to_die = ft_atoi(argv[2]);
	god->time_to_eat = ft_atoi(argv[3]);
	god->time_to_sleep = ft_atoi(argv[4]);
	god->n_times_eat = -1;
	if (argv[5])
		god->n_times_eat = ft_atoi(argv[5]);
}
