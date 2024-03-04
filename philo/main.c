/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:01:45 by davifern          #+#    #+#             */
/*   Updated: 2024/03/04 20:39:29 by davifern         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_god	*god;

	if (check_input(argc, argv))
		return (exit_error(1));
	if (argv[1][0] == '0')
		return (0);
	god = create_god(argv);
	if (!god)
		return (exit_error(2));
	if (create_philos_and_start_threads(god, routine))
		return (clean_and_destroy(god), exit_error(3));
	int i = 0;
	while (i < god->n_philo)
	{
		if (pthread_create(&god->philo[i].th, NULL, routine, &god->philo[i])) //começa a thread
			return (3);
		// god->philo[i].fasting = get_time(god->start);
		// table->philos[i].last_meal = timestamp(); O Aitor e Sebas fazem depois de criar a thread
		i++;
	}
	
	//The observer
	// int		i;
	i = 0;
	while (god->all_alive)
	{
		// while (i < god->n_philo && god->all_alive) //TODO: ver se preciso do all_alive
		while (i < god->n_philo)
		{
			if (philosopher_died(&god->philo[i]))
			{
				// pthread_mutex_lock(&god->mutex_all_alive); //subir para antes do philosopher_died no caso de printar depois da morte
				god->all_alive = 0;
				// pthread_mutex_unlock(&god->mutex_all_alive);
				break ;
			}
			i++;
		}
		// usleep(100); aitor faz isso... pq nao sei
		i = 0;
	}
	if (wait_threads(god))
		return (clean_and_destroy(god), exit_error(4));
	return (clean_and_destroy(god));
}
/*
	//TODO: All phisolophers eat enough?
	Código abaixo aparentemente verifica isso
	i = 0;
	int	a = 0;
	while(1)
	{
		if (god->n_times_eat < 0)
			break ;
		while (i <= god->n_philo)
		{
			if (god->philo[i].times_eaten == god->n_times_eat)
			{
				printf("philo #%d comió comió el suficiente, a = %d\n", god->philo[i].id, a);
				a++;
			}
			i++;
		}
		if (a == god->n_times_eat)
		{
			printf("Todos comieron lo suficiente\n");
			break ;
			//aqui devo terminar o programa
		}
		a = 0;
		i = 0;
	}
*/