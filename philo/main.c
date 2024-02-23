/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:01:45 by davifern          #+#    #+#             */
/*   Updated: 2024/02/23 16:19:55 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_philo	*create_philo(char **argv, struct timeval start)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	gettimeofday(&philo->fasting, NULL);
	gettimeofday(&philo->now, NULL);
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
	// t_god	*god;

	// god = (t_god *)god_data;
	philo = (t_philo *)philo_data;
	
	gettimeofday(&philo->now, NULL);
	while (!philosopher_died(philo->fasting, philo->now, philo->time_to_die)) //passar philo depois
	{
		gettimeofday(&philo->now, NULL); //talvez possa remover as condições de morte e o gettimeofday daqui
		printf("%.5lu X has taken a fork\n", get_current_time(philo->start, philo->now));
		if (!philosopher_died(philo->fasting, philo->now, philo->time_to_die)) //come
		{
			printf("%.5lu X is eating\n", get_current_time(philo->start, philo->now));
			usleep(philo->time_to_eat * 1000);
			gettimeofday(&philo->fasting, NULL); //começa o jejum
		}
		
		gettimeofday(&philo->now, NULL);
		if (!philosopher_died(philo->fasting, philo->now, philo->time_to_die)) //dorme
		{
			printf("%.5lu X is sleeping\n", get_current_time(philo->start, philo->now));
			usleep(philo->time_to_sleep * 1000);
		}
		
		gettimeofday(&philo->now, NULL);
		printf("%.5lu X is thinking\n", get_current_time(philo->start, philo->now)); //pensa
	}
	printf("%.5lu X died\n", get_current_time(philo->start, philo->now)); //morre
	
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	tid1;
	struct timeval start;
	int	number_of_philosophers;
	// t_philo **philo_list;
	t_philo	*philo = NULL;
	// t_god	*god;

	if (check_input(argc, argv))
		return (1);
	
	number_of_philosophers = ft_atoi(argv[1]);
	(void)number_of_philosophers;
	// philo_list = (t_philo **)malloc(number_of_philosophers * sizeof(philo));
	// philo_list[0] = philo;

	// god = create_god();
	gettimeofday(&start, NULL);
	philo = create_philo(argv, start);
	// god->philo = philo;
	
	
	pthread_create(&tid1, NULL, routine, (void *)philo);
	pthread_join(tid1, NULL);



	

	return (0);
}
	// printf("Number of philosophers: %d\n"
	// 	"Time to die: %d\nTime to eat: %d\nTime to sleep: %d\n"
	// 	"# times each philosopher must eat: %d\nStart time: %lu\n", number_of_philosophers,
	// 	god->philo->time_to_die, god->philo->time_to_eat, god->philo->time_to_sleep, god->philo->n_times_eat, god->start.tv_sec);