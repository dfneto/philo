/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:01:45 by davifern          #+#    #+#             */
/*   Updated: 2024/03/15 16:37:03 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
* pthread_mutex_lock(&god->mutex_fork[i]) : if the mutex is already locked by 
* a different thread, the calling thread will block (i.e., wait) until the mutex 
* becomes available. This means that the thread attempting to acquire the lock
* will be suspended and placed in a wait state until the thread that currently 
* holds the lock releases it. Em outras palavras, pega (bloqueia) o garfo i se
* não estiver bloqueado 

* pthread_join: é como um wait para thread. Não executa nada depois até que a
* thread i termine sua execução
*/

#include "philo.h"

void	run_observer(t_god *god)
{
	// int		philos_fed;
	int		i;

	i = 0;
	// philos_fed = 0;
	while (god->all_alive)
	{
		i = 0;
		while (i < god->n_philo)
		{
			if (philosopher_died(&god->philo[i]))
			{
				pthread_mutex_lock(&god->mutex_all_alive); //Acho que posso remover isso e simplesmente sair do run observer como a julia faz
				god->all_alive = 0;
				pthread_mutex_unlock(&god->mutex_all_alive);
				usleep(50);
				print(&god->philo[i], DIE);
				return ;
			}
			pthread_mutex_lock(&god->philo[i].m_eat);
			if (god->n_times_eat > 0 && god->philo[i].times_eaten == god->n_times_eat) //se um philo comeu o suficiente ...
			{
				//TODO: implementar se os filósofos comeram o suficiente
			}
			pthread_mutex_unlock(&god->philo[i].m_eat);
			i++;
		}
		// i = 0;
		// while (i < god->n_philo)
		// {
		// 	pthread_mutex_lock(&god->philo[i].m_eat);
		// 	if (god->n_times_eat > 0 && god->philo[i].times_eaten == god->n_times_eat) //se um philo comeu o suficiente ...
		// 	{
		// 		if (i == god->n_philo - 1)
		// 			philos_fed = 1; //o ultimo comeu o suficiente
		// 	}
		// 	pthread_mutex_unlock(&god->philo[i].m_eat);
		// 	if (god->n_times_eat > 0 && god->philo[i].times_eaten < god->n_times_eat) //se um philo NÃO comeu o suficiente ...
		// 		break ;
		// 	i++;
		// }
	}
}

int	create_threads(t_god *god)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&god->m_start);
	while (i < god->n_philo)
	{
		if (pthread_create(&god->philo[i].th, NULL, routine, &god->philo[i]))
			return (3);
		i++;
	}
	god->start = get_current_time();
	pthread_mutex_unlock(&god->m_start);
	return (0);
}

int	main(int argc, char **argv)
{
	t_god	*god;

	if (check_input(argc, argv))
		return (exit_error(1));
	god = create_god(argv);
	if (!god)
		return (exit_error(2));
	create_philos(god);
	// if (create_threads(god))
	// 	return (clean_and_destroy(god), exit_error(3));
	
	pthread_t	*threads;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * god->n_philo);
	if (!threads)
		return (exit_error(2));
	int	i;
	i = 0;
	pthread_mutex_lock(&god->m_start);
	while (i < god->n_philo)
	{
		if (pthread_create(&threads[i], NULL, routine, &god->philo[i]))
			return (3);
		i++;
	}
	god->start = get_current_time();
	pthread_mutex_unlock(&god->m_start);


	run_observer(god);
	// if (wait_threads(god))
	// 	return (clean_and_destroy(god), exit_error(4));
	while (--i > 0)
	{
		if (pthread_join(threads[i], NULL))
			return (4);
	}



	return (clean_and_destroy(god));
}
