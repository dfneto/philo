/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:01:45 by davifern          #+#    #+#             */
/*   Updated: 2024/02/24 02:17:25 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//Check if one philosopher died and finish execution
//Mutex the fork

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

// t_god	*create_god()
// {
// 	t_god	*god;

// 	god = (t_god *)malloc(sizeof(t_god));
// 	if (!god)
// 		return (NULL);
// 	gettimeofday(&god->start, NULL);
// 	god->philo = NULL;
// 	return (god);
// }

t_philo	*create_philo(char **argv, struct timeval start, int id)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	gettimeofday(&philo->fasting, NULL);
	gettimeofday(&philo->now, NULL);
	philo->id = id;
	philo->start = start;	
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->n_times_eat = 0;
	if (argv[5])
		philo->n_times_eat = ft_atoi(argv[5]);
	return (philo);
}

void	*routine(void *philo_data)
{
	// faço na criação do philo
	// gettimeofday(&start, NULL);
	// gettimeofday(&fasting, NULL);

	// usleep(3000);//simulacao para que now > fasting
	t_philo *philo;
	int		i = 1;
	// t_god	*god;

	// god = (t_god *)god_data;
	philo = (t_philo *)philo_data;
	
	gettimeofday(&philo->now, NULL);
	while (!philosopher_died(philo->fasting, philo->now, philo->time_to_die) && i <= philo->n_times_eat) //TODO: refactor
	{
		gettimeofday(&philo->now, NULL); //talvez possa remover as condições de morte e o gettimeofday daqui
		printf("%.5lu %d has taken a fork\n", get_current_time(philo->start, philo->now), philo->id);
		if (!philosopher_died(philo->fasting, philo->now, philo->time_to_die)) //come
		{
			printf("%.5lu %d is eating\n", get_current_time(philo->start, philo->now), philo->id);
			i++;
			usleep(philo->time_to_eat * 1000);
			gettimeofday(&philo->fasting, NULL); //começa o jejum
		}
		
		gettimeofday(&philo->now, NULL);
		if (!philosopher_died(philo->fasting, philo->now, philo->time_to_die)) //dorme
		{
			printf("%.5lu %d is sleeping\n", get_current_time(philo->start, philo->now), philo->id);
			usleep(philo->time_to_sleep * 1000);
		}
		
		gettimeofday(&philo->now, NULL);
		printf("%.5lu %d is thinking\n", get_current_time(philo->start, philo->now), philo->id); //pensa
	}
	printf("%.5lu %d died\n", get_current_time(philo->start, philo->now), philo->id); //morre
	
	return (NULL);
}

int	main(int argc, char **argv)
{
	int				i = 0;
	int				number_of_philosophers;
	struct timeval 	start;
	pthread_t		*tid;
	t_philo			**philo;

	if (check_input(argc, argv))
		return (1);
	number_of_philosophers = ft_atoi(argv[1]);
	tid = (pthread_t *)malloc(number_of_philosophers * sizeof(pthread_t));
	if (!tid)
		return (1);

	philo = (t_philo **)malloc(number_of_philosophers * sizeof(t_philo *));
	if (!philo)
		return (1);

	gettimeofday(&start, NULL);

	while (i < number_of_philosophers)
	{
		philo[i] = create_philo(argv, start, i);
		pthread_create(&tid[i], NULL, routine, (void *)philo[i]);
		i++;
	}
	i = 0;
	while (i < number_of_philosophers)
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