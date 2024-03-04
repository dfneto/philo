/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:47:05 by davifern          #+#    #+#             */
/*   Updated: 2024/03/04 20:41:47 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(long long time, t_god *god)
{
	long long	current;

	current = get_time(god->start);
	while (1)
	{
		if (current - get_time(god->start) >= time)
			break ;
		usleep(100);
	}
}

void	*routine(void *philo_data)
{
	t_philo *philo;
	t_god	*god;
	int		left = 0;

	long long sleep_init = 0;

	philo = (t_philo *)philo_data;
	god = philo->god;
	// philo->fasting = get_time(god->start);
	set_philo_to_start(philo);
	// while (all_alive(god)) //evita data race
	while (god->all_alive)
	{
		pthread_mutex_lock(&god->mutex_fork[philo->id]);
		print(philo, FORK);
		// if (god->n_philo == 1)
		// {
		// 	pthread_mutex_unlock(&god->mutex_fork[philo->id]);
		// 	break; 
		// }
		left = define_left_fork(philo);
		pthread_mutex_lock(&god->mutex_fork[left]);
		print(philo, FORK);
		
		print(philo, EAT);
		// pthread_mutex_lock(&philo->m_fasting);
		// pthread_mutex_lock(&god->m_god_fasting);
		philo->fasting = get_time(god->start);
		// pthread_mutex_unlock(&god->m_god_fasting);
		// pthread_mutex_unlock(&philo->m_fasting);
		philo->times_eaten++;
		// usleep(god->time_to_eat * 1000);
		// ft_sleep(god->time_to_eat, philo->god);
		sleep_init = get_time(philo->god->start);
		while (get_time(philo->god->start) - sleep_init <= (long long)philo->god->time_to_eat)
			;
		pthread_mutex_unlock(&god->mutex_fork[philo->id]);
		pthread_mutex_unlock(&god->mutex_fork[left]);
		
		print(philo, SLEEP);
		// usleep(god->time_to_sleep * 1000);
		// ft_sleep(god->time_to_sleep, philo->god);
		sleep_init = get_time(philo->god->start);
		while (get_time(philo->god->start) - sleep_init <= (long long)philo->god->time_to_sleep)
			;
		
		print(philo, THINK);
	}
	return (NULL);
}
