/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:01:45 by davifern          #+#    #+#             */
/*   Updated: 2024/02/27 11:00:40 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO: Check if one philosopher died and finish execution
//TODO: stops when all phisolophers eat enough
//TODO: Mutex the fork

#include "philo.h"
#include <unistd.h>
#include <pthread.h>

void	*routine(void *philo_data)
{
	t_philo *philo;
	t_god	*god;
	int		i = 1;

	philo = (t_philo *)philo_data;
	god = philo->god;
	printf("philosofer #%d, all_alive: %d\n", philo->id, god->all_alive);
	while (all_alived(philo))
	{
		printf("%.5lld %d has taken a fork\n", get_time(god->start), philo->id);
		if (all_alived(philo)) //come
		{
			printf("%.5lld %d is eating\n", get_time(god->start), philo->id);
			i++;
			usleep(god->time_to_eat * 1000);
			philo->fasting = get_time(god->start);//começa o jejum
		}
		
		if (all_alived(philo)) //dorme
		{
			printf("%.5lld %d is sleeping\n", get_time(god->start), philo->id);
			usleep(god->time_to_sleep * 1000);
		}
		
		printf("%.5lld %d is thinking\n", get_time(god->start), philo->id); //pensa
	}
	philosopher_die(philo);
	
	
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
		god->philo[i].id = i;
		god->philo[i].god = god;
		god->philo[i].fasting = get_time(god->start);
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
	// 	"# times each philosopher must eat: %d\nStart time: %lld\n", number_of_philosophers,
	// 	god->philo->time_to_die, god->philo->time_to_eat, god->philo->time_to_sleep, god->philo->n_times_eat, god->start.tv_sec);