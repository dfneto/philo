/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_conditions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:24:32 by davifern          #+#    #+#             */
/*   Updated: 2024/03/06 13:25:40 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
* Return 0: if the god->n_times_eat was not set (so it is -1) or
* if the philosophers didn't still eat enough.
*/
int	eat_enough(t_philo *philo)
{
	if (philo->god->n_times_eat < 0)
		return (0);
	if (philo->times_eaten < philo->god->n_times_eat)
		return (0);
	return (1);
}

/*
* Returns:
*	1 - if the philospher died
*	0 - if the philospher did not die
*/
int		philosopher_died(t_philo *philo)
{
	long long		time_now;
	int				ret;

	ret = 0;
	pthread_mutex_lock(&philo->m_last_meal);
	time_now = get_time(philo->god->start);
	if (time_now - philo->last_meal >= philo->god->time_to_die)
	{
		print(philo, DIE);
		ret = 1;
	}
	pthread_mutex_unlock(&philo->m_last_meal);
	return (ret);
	
}

int	all_alive(t_god *god)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&god->mutex_all_alive);
	if (god->all_alive)
		ret = 1;
	pthread_mutex_unlock(&god->mutex_all_alive);
	return (ret);
}
