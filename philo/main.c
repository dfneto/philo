/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:01:45 by davifern          #+#    #+#             */
/*   Updated: 2024/02/27 20:00:50 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO: Mutex the fork. O garfo tá disponível? Pego e seguro até o outro estar disponível.
//TODO: Soltar o garfo quando um deles não está disponível
//TODO: stops when all phisolophers eat enough
//TODO: um filósofo pode morrer enquanto come?
//TODO: da ultima vez que comeu até a morte tem que passar tiempo de muerto (+tempo de comer) + 10s
//TODO: testar com 0, 1, 5, 10 e 200
//TODO: testar data race
//TODO: Check if one philosopher died and finish execution - OK

#include "philo.h"
#include <unistd.h>


void	*routine(void *philo_data)
{
	t_philo *philo;
	t_god	*god;
	int		i = 1;

	philo = (t_philo *)philo_data;
	god = philo->god;
	while (all_alived(philo))
	{
		//pegar os garfos
		while (all_alived(philo) && god->fork[i] == 0)
		{
			//TODO: refatorar tudo aqui porque 
			// If the mutex is already locked by a different thread, the calling thread will block (i.e., wait) until the mutex becomes available. This means that the thread attempting to acquire the lock will be suspended and placed in a wait state until the thread that currently holds the lock releases it.
			//pthread_mutex_lock(&god->mutex_fork[i]); // pega o garfo direto fork[i] quando não estiver bloqueado
			pthread_mutex_lock(&god->mutex_fork[i]); // lock right fork
			god->fork[i] = 1; 	//pega o garfo direto fork[i]
			printf("%.5lld %d has taken a fork\n", get_time(god->start), philo->id);
		}
		while (all_alived(philo) && fork[i - 1] == 0)
		{
			lock
			fork[i - 1] = 1; //pega o garfo esquerdo
			printf("%.5lld %d has taken a fork\n", get_time(god->start), philo->id);
		}

		
		if (all_alived(philo)) //come
		{
			printf("%.5lld %d is eating\n", get_time(god->start), philo->id);
			i++;
			usleep(god->time_to_eat * 1000);
			//unlock the forks
			//fork[i] = 0;
			//fork[i - 1] = 0;
			philo->fasting = get_time(god->start);//começa o jejum
		}
		if (all_alived(philo)) //dorme
		{
			printf("%.5lld %d is sleeping\n", get_time(god->start), philo->id);
			usleep(god->time_to_sleep * 1000);
		}
		if (all_alived(philo))
			printf("%.5lld %d is thinking\n", get_time(god->start), philo->id); //pensa
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int				i = 0;
	pthread_t		*tid = NULL; //TODO: passar a thread para dentro do filósofo
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
		// printf("Thread %d has finished execution\n", i);
		i++;
	}
	pthread_mutex_destroy(&god->mutex);
	//TODO: free do tid e god e dos philos, mas antes rodar o leaks atExit
	return (0);
}
	// printf("Number of philosophers: %d\n"
	// 	"Time to die: %d\nTime to eat: %d\nTime to sleep: %d\n"
	// 	"# times each philosopher must eat: %d\nStart time: %lld\n", number_of_philosophers,
	// 	god->philo->time_to_die, god->philo->time_to_eat, god->philo->time_to_sleep, god->philo->n_times_eat, god->start.tv_sec);