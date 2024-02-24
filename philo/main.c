/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:01:45 by davifern          #+#    #+#             */
/*   Updated: 2024/02/24 14:05:48 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO: Check if one philosopher died and finish execution
//TODO: stops when all phisolophers eat enough
//TODO: Mutex the fork

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

t_god	*create_god(char **argv)
{
	t_god	*god;
	
	god = (t_god *)malloc(sizeof(t_god));
	if (!god)
		return (NULL);
	gettimeofday(&god->start, NULL);
	gettimeofday(&god->now, NULL);
	god->all_alive = 1;
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

t_philo	*create_philo(int id)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	gettimeofday(&philo->fasting, NULL);
	philo->id = id;
	return (philo);
}

void	*routine(void *philo_data)
{
	printf("AQUI\n");
	t_philo *philo;
	t_god	*god;
	int		i = 1;

	philo = (t_philo *)philo_data;
	god = philo->god;

	gettimeofday(&god->now, NULL);
	printf("philosofer #%d, all_alive: %d\n", philo->id, god->all_alive);
	if (philo->id == 0)
		god->all_alive = 9;
	//&& i <= philo->n_times_eat
	while (!philosopher_died(philo->fasting, god->now, god->time_to_die) && god->all_alive == 1) //TODO: refactor
	{
		gettimeofday(&god->now, NULL); //talvez possa remover as condições de morte e o gettimeofday daqui
		printf("%.5lu %d has taken a fork\n", get_current_time(god->start, god->now), philo->id);
		if (!philosopher_died(philo->fasting, god->now, god->time_to_die) && god->all_alive == 1) //come
		{
			printf("%.5lu %d is eating\n", get_current_time(god->start, god->now), philo->id);
			i++;
			usleep(god->time_to_eat * 1000);
			gettimeofday(&philo->fasting, NULL); //começa o jejum
		}
		
		gettimeofday(&god->now, NULL);
		if (!philosopher_died(philo->fasting, god->now, god->time_to_die) && god->all_alive == 1) //dorme
		{
			printf("%.5lu %d is sleeping\n", get_current_time(god->start, god->now), philo->id);
			usleep(god->time_to_sleep * 1000);
		}
		
		gettimeofday(&god->now, NULL);
		printf("%.5lu %d is thinking\n", get_current_time(god->start, god->now), philo->id); //pensa
	}
	printf("%.5lu %d died\n", get_current_time(god->start, god->now), philo->id); //morre
	god->all_alive = 0;
	
	return (NULL);
}

int	main(int argc, char **argv)
{
	int				i = 0;
	pthread_t		*tid = NULL;
	t_god			*god;

	if (check_input(argc, argv))
		return (1);
	god = create_god(argv);
	if (!god)
		return (-1);
	tid = (pthread_t *)malloc(god->n_philo * sizeof(pthread_t));
	if (!tid)
		return (-1);
	while (i < god->n_philo)
	{
		god->philo[i].id = i; //nao tenho muito claro como funcinoa na memória isso
		gettimeofday(&god->philo[i].fasting, NULL);
		god->philo[i].god = god;
		pthread_create(&tid[i], NULL, routine, &god->philo[i]);
		i++;
	}
	i = 0;
	while (i < god->n_philo)
	{
		pthread_join(tid[i], NULL);
		printf("Thread %d has finished execution\n", i);
		i++;
	}
	return (0);
}
	// printf("Number of philosophers: %d\n"
	// 	"Time to die: %d\nTime to eat: %d\nTime to sleep: %d\n"
	// 	"# times each philosopher must eat: %d\nStart time: %lu\n", number_of_philosophers,
	// 	god->philo->time_to_die, god->philo->time_to_eat, god->philo->time_to_sleep, god->philo->n_times_eat, god->start.tv_sec);