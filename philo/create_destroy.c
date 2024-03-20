/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:16:29 by davifern          #+#    #+#             */
/*   Updated: 2024/03/20 16:13:43 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_god	*create_god(char **argv)
{
	t_god	*god;
	int		i;

	i = 0;
	god = (t_god *)malloc(sizeof(t_god));
	if (!god)
		return (NULL);
	get_input_data(argv, god);
	god->all_alive = 1;
	god->fed_philos = 0;
	pthread_mutex_init(&god->mutex_all_alive, NULL);
	pthread_mutex_init(&god->m_print, NULL);
	pthread_mutex_init(&god->m_start, NULL);
	god->mutex_fork = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * god->n_philo);
	if (!god->mutex_fork)
		return (NULL);
	while (i < god->n_philo)
		pthread_mutex_init(&god->mutex_fork[i++], NULL);
	god->philo = (t_philo *)malloc(sizeof(t_philo) * god->n_philo);
	if (!god->philo)
		return (NULL);
	return (god);
}

void	create_philos(t_god *god)
{
	int			i;

	i = 0;
	while (i < god->n_philo)
	{
		god->philo[i].id = i;
		god->philo[i].times_eaten = 0;
		god->philo[i].god = god;
		pthread_mutex_init(&god->philo[i].m_eat, NULL);
		i++;
	}
}

int	clean_and_destroy(t_god *god)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&god->mutex_all_alive);
	pthread_mutex_destroy(&god->m_print);
	pthread_mutex_destroy(&god->m_start);
	while (i < god->n_philo)
	{
		pthread_mutex_destroy(&god->mutex_fork[i]);
		pthread_mutex_destroy(&god->philo[i].m_eat);
		i++;
	}
	free(god->mutex_fork);
	free(god->philo);
	free(god);
	return (0);
}

int	wait_threads(t_god *god)
{
	int	i;

	i = 0;
	while (i < god->n_philo)
	{
		if (pthread_join(god->philo[i].th, NULL))
			return (4);
		i++;
	}
	return (0);
}
