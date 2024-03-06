/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:47:05 by davifern          #+#    #+#             */
/*   Updated: 2024/03/06 20:42:49 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*deal_one_child_case(t_philo *philo)
{
	philo->last_meal = get_time(philo->god->start);
	print(philo, FORK);
	ft_sleep(philo->god->time_to_sleep);
	return (NULL);
}

void	execute_core_rotine(t_philo *philo, t_god *god, int left)
{
	pthread_mutex_lock(&god->mutex_fork[philo->id]);
	print(philo, FORK);
	pthread_mutex_lock(&god->mutex_fork[left]);
	print(philo, FORK);
	print(philo, EAT);
	ft_sleep(god->time_to_eat);
	pthread_mutex_unlock(&god->mutex_fork[philo->id]);
	pthread_mutex_unlock(&god->mutex_fork[left]);
	pthread_mutex_lock(&philo->m_times_eaten);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->m_times_eaten);
	pthread_mutex_lock(&philo->m_last_meal);
	philo->last_meal = get_time(god->start);
	pthread_mutex_unlock(&philo->m_last_meal);
	print(philo, SLEEP);
	ft_sleep(god->time_to_sleep);
	print(philo, THINK);
}

/*
* O lock e unlock do start não chegou a me dar um ganho de tempo,
* mas gostei da ideia de forçar com que todas as threads comecem 
* "juntas"
* pthread_mutex_lock(&god->m_start); 
* pthread_mutex_unlock(&god->m_start);
*/
void	*routine(void *philo_data)
{
	int		left;
	t_philo	*philo;
	t_god	*god;

	philo = (t_philo *)philo_data;
	god = philo->god;
	set_philo_to_start(philo);
	if (god->n_philo == 1)
		return (deal_one_child_case(philo));
	left = define_left_fork(philo);
	pthread_mutex_lock(&god->m_start);
	pthread_mutex_unlock(&god->m_start);
	while (all_alive(god) && !eat_enough(philo))
		execute_core_rotine(philo, god, left);
	return (NULL);
}
