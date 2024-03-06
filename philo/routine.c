/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:47:05 by davifern          #+#    #+#             */
/*   Updated: 2024/03/06 13:12:26 by davifern         ###   ########.fr       */
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
	if (god->n_philo == 1)
	{
		print(philo, FORK);
		ft_sleep(god->time_to_sleep);
		return (NULL); 
	}
	left = define_left_fork(philo);
	
	pthread_mutex_lock(&god->m_start); //não muda nada, mas gostei da ideia
	pthread_mutex_unlock(&god->m_start);
	// philo->last_meal = get_time(god->start); da leaks
	while (all_alive(god) && !eat_enough(philo))
	{
		pthread_mutex_lock(&god->mutex_fork[philo->id]);
		print(philo, FORK);
		pthread_mutex_lock(&god->mutex_fork[left]);
		print(philo, FORK);
		print(philo, EAT);
		pthread_mutex_lock(&philo->m_last_meal);
		philo->last_meal = get_time(god->start);
		pthread_mutex_unlock(&philo->m_last_meal);
		pthread_mutex_lock(&philo->m_times_eaten);
		philo->times_eaten++;
		pthread_mutex_unlock(&philo->m_times_eaten);
		ft_sleep(god->time_to_eat);
		pthread_mutex_unlock(&god->mutex_fork[philo->id]);
		pthread_mutex_unlock(&god->mutex_fork[left]);
		print(philo, SLEEP);
		ft_sleep(god->time_to_sleep);
		print(philo, THINK);
	}
	return (NULL);
}
