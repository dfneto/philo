/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:01:45 by davifern          #+#    #+#             */
/*   Updated: 2024/02/29 12:41:43 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO: criar uma thread (outra rotina com mesmo god) que observa se os filósofos estão vivos e se um morreu imprime que ela morreu pq pense no exe: 2 filósofos
// que levam 300ms para comer e 200ms para morrer. Quando o primeiro come o segundo vai morrer em 200ms contudo como ele que vai printar
// sua morte, vai printar em 300 e não 200. make && ./philo 2 100 300 100
//TODO: da ultima vez que comeu até a morte tem que passar tiempo de muerto (+tempo de comer) + 10s
//TODO: stops when all phisolophers eat enough

//TODO: testar com 0, 1, 5, 10 e 200 filósofos. Testar com diferentes tempos e com -1, 0, n times_to_eat
//TODO: testar data race
//TODO: Check if one philosopher died and finish execution - OK
//TODO: Mutex the fork. O garfo tá disponível? Pego e seguro até o outro estar disponível. - OK
//TODO: Soltar o garfo quando um deles não está disponível - No voy a hacer

#include "philo.h"


/* pthread_mutex_lock(&god->mutex_fork[i]) : if the mutex is already locked by 
a different thread, the calling thread will block (i.e., wait) until the mutex 
becomes available. This means that the thread attempting to acquire the lock
will be suspended and placed in a wait state until the thread that currently 
holds the lock releases it. */

int	define_left_fork(t_philo *philo)
{
	if (philo->id == 0)
		return (philo->god->n_philo - 1);
	else
		return (philo->id - 1);
}

void	*routine(void *philo_data)
{
	t_philo *philo;
	t_god	*god;
	int		left = 0;
	// int		a = 1;

	philo = (t_philo *)philo_data;
	god = philo->god;
	set_philo_to_start(philo);
	while (all_alived(philo))
	{
		pthread_mutex_lock(&god->mutex_fork[philo->id]); // pega (lock) o garfo DIREITO quando não estiver bloqueado
		if (all_alived(philo)) 
			printf("%.5lld %d has taken a fork %d\n", get_time(god->start), philo->id, philo->id);
		left = define_left_fork(philo);
		pthread_mutex_lock(&god->mutex_fork[left]); // pega (lock) o garfo ESQUERDO quando não estiver bloqueado
		if (all_alived(philo))
			printf("%.5lld %d has taken a fork %d\n", get_time(god->start), philo->id, left);
		if (all_alived(philo)) //EAT
		{
			printf("%.5lld %d is eating\n", get_time(god->start), philo->id);
			philo->times_eaten++;
			usleep(god->time_to_eat * 1000);
			philo->fasting = get_time(god->start); //FASTING STARTS
		}
		pthread_mutex_unlock(&god->mutex_fork[philo->id]); //unlock RIGHT fork
		printf("philo %d Unlock right fork %d\n", philo->id, philo->id);
		pthread_mutex_unlock(&god->mutex_fork[left]); // unlock LEFT fork
		printf("philo %d Unlock left fork %d\n", philo->id, left);
		if (all_alived(philo)) //SLEEP
		{
			printf("%.5lld %d is sleeping\n", get_time(god->start), philo->id);
			usleep(god->time_to_sleep * 1000);
		}
		if (all_alived(philo))
			printf("%.5lld %d is thinking\n", get_time(god->start), philo->id); //THINK
	}
	printf("Filósofo #%d ha parado su ejecución\n", philo->id);
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
		god->philo[i].times_eaten = 0;
		god->philo[i].god = god;
		god->philo[i].fasting = get_time(god->start);
		pthread_create(&tid[i], NULL, routine, &god->philo[i]); //começa a thread
		i++;
	}
	
	//TODO: solamente hacer el join despues que todos comieron o uno si morrió
	i = 0;
	

	while (i < god->n_philo)
	{
		pthread_join(tid[i], NULL);		//espera pela thread
		printf("Thread %d has finished execution\n", i);
		i++;
	}
	printf("passou\n");
	// pthread_mutex_destroy(&god->mutex_all_alive);
	// i = 0;
	// while (i < god->n_philo)
	// 	pthread_mutex_destroy(&god->mutex_fork[i++]);
	// free(god->mutex_fork);
	//TODO: free do tid e god e dos philos, mas antes rodar o leaks atExit
	return (0);
}
	// printf("Number of philosophers: %d\n"
	// 	"Time to die: %d\nTime to eat: %d\nTime to sleep: %d\n"
	// 	"# times each philosopher must eat: %d\nStart time: %lld\n", number_of_philosophers,
	// 	god->philo->time_to_die, god->philo->time_to_eat, god->philo->time_to_sleep, god->philo->n_times_eat, god->start.tv_sec);