/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:47:05 by davifern          #+#    #+#             */
/*   Updated: 2024/03/02 10:47:20 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_data)
{
	t_philo *philo;
	t_god	*god;
	int		left = 0;

	philo = (t_philo *)philo_data;
	god = philo->god;
	set_philo_to_start(philo);
	while (all_alive(god))
	{
		pthread_mutex_lock(&god->mutex_fork[philo->id]);
		if (all_alive(god)) 
			print(philo, FORK);
		left = define_left_fork(philo);
		pthread_mutex_lock(&god->mutex_fork[left]);
		if (all_alive(god))
			print(philo, FORK);
		if (all_alive(god))
		{
			print(philo, EAT);
			pthread_mutex_lock(&philo->m_fasting);
			philo->fasting = get_time(god->start);
			pthread_mutex_unlock(&philo->m_fasting);
			philo->times_eaten++;
			usleep(god->time_to_eat * 1000);
		}
		pthread_mutex_unlock(&god->mutex_fork[philo->id]);
		pthread_mutex_unlock(&god->mutex_fork[left]);
		if (all_alive(god))
		{
			print(philo, SLEEP);
			usleep(god->time_to_sleep * 1000);
		}
		if (all_alive(god))
			print(philo, THINK);
	}
	return (NULL);
}