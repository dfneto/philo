/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:47:05 by davifern          #+#    #+#             */
/*   Updated: 2024/03/05 15:44:30 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
* Fazemos nossa função de sleep porque usleep espera o tempo e mais um pouquinho.
* Ex: você pede para dormir 100ms (usleep(100*1000)) e ele dorme 102ms.
* Acrescentamos um usleep(100) no loop para não sobrecarregar o processador neste 
* loop infinito. Então dizemos: calcule o if e espere 100us, depois calcule e 
* espere e então o processador pode fazer outra coisa. Ao invés de:
* calcule, calcule, calcule infinitamente.
* usleep(10): é evitar que imprima algo depois de morto
*/
// void	ft_sleep(long long time, t_god *god)
// {
// 	long long	init_time;
	
// 	init_time = get_time(god->start);
// 	while (1)
// 	{
// 		if (get_time(god->start) - init_time >= time)
// 			break ;
// 		usleep(100);
// 	}
// 	usleep(10);
// }

void	ft_sleep(long long time)
{
	long long	limit_time;

	limit_time = get_current_time() + time;
	while (1)
	{
		if (get_current_time() >= limit_time)
			break ;
		usleep(100);
	}
}

void	*routine(void *philo_data)
{
	t_philo *philo;
	t_god	*god;
	int		left = 0;

	philo = (t_philo *)philo_data;
	god = philo->god;
	set_philo_to_start(philo);
	if (god->n_philo == 1)
	{
		print(philo, FORK);
		ft_sleep(god->time_to_sleep);
		return (NULL); 
	}
	left = define_left_fork(philo);
	
	pthread_mutex_lock(&god->m_start);
	pthread_mutex_unlock(&god->m_start);
	philo->fasting = get_time(god->start);
	
	while (all_alive(god))
	{
		pthread_mutex_lock(&god->mutex_fork[philo->id]);
		print(philo, FORK);
		pthread_mutex_lock(&god->mutex_fork[left]);
		print(philo, FORK);
		print(philo, EAT);
		pthread_mutex_lock(&philo->m_fasting);
		philo->fasting = get_time(god->start);
		pthread_mutex_unlock(&philo->m_fasting);
		philo->times_eaten++;
		ft_sleep(god->time_to_eat);
		pthread_mutex_unlock(&god->mutex_fork[philo->id]);
		pthread_mutex_unlock(&god->mutex_fork[left]);
		print(philo, SLEEP);
		ft_sleep(god->time_to_sleep);
		print(philo, THINK);
	}
	return (NULL);
}
