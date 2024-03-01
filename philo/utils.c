/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:01:07 by davifern          #+#    #+#             */
/*   Updated: 2024/03/01 16:10:02 by davifern         ###   ########.fr       */
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
	god->all_alive = 1;
	god->start = get_start_time();
	god->n_philo = ft_atoi(argv[1]);
	god->time_to_die = ft_atoi(argv[2]);
	god->time_to_eat = ft_atoi(argv[3]);
	god->time_to_sleep = ft_atoi(argv[4]);
	god->n_times_eat = -1;
	if (argv[5])
		god->n_times_eat = ft_atoi(argv[5]);
	pthread_mutex_init(&god->mutex_all_alive, NULL);
	pthread_mutex_init(&god->m_print, NULL);
	god->mutex_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * god->n_philo);
	if (!god->mutex_fork)
		return (NULL);
	while (i < god->n_philo)
	{
		pthread_mutex_init(&god->mutex_fork[i], NULL);
		i++;
	}
	god->philo = (t_philo *)malloc(sizeof(t_philo) * god->n_philo);
	if (!god->philo)
		return (NULL);
	return (god);
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
	time_now = get_time(philo->god->start);
	pthread_mutex_lock(&philo->m_fasting); 
	if (time_now - philo->fasting > philo->god->time_to_die)
	{
		print(philo, DIE);
		ret = 1;
	}
	pthread_mutex_unlock(&philo->m_fasting);
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

/*
* Usamos un mutex para imprimir porque así se cría una cola de impresión
* y garantizamos que un filósofo va a imprimir por vez y cuando este va 
* a imprimir, él también va a coger el tiempo actual. Sin este mutex es 
* posible que un filósofo coja el tiempo 20 y el otro coja el tiempo 21, 
* imprima su acción con el tiempo 21 y solamente después que el otro
* filósofo va a imprimir su acción con el tiempo 20.
*/
void	print(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->god->m_print);
	if (status == FORK)
		printf("%.5lld %d has taken a fork\n", get_time(philo->god->start), philo->id);
	if (status == EAT)
		printf("%.5lld %d is eating\n", get_time(philo->god->start), philo->id);
	if (status == SLEEP)
		printf("%.5lld %d is sleeping\n", get_time(philo->god->start), philo->id);
	if (status == THINK)
		printf("%.5lld %d is thinkings\n", get_time(philo->god->start), philo->id);
	if (status == DIE)
		printf("\033[31m%.5lld %d died\033[0m\n", get_time(philo->god->start), philo->id);
	pthread_mutex_unlock(&philo->god->m_print);
}

/*
* Los filósofos impares y el último duermen por 1ms. 
* Esta función es para tratar la concurrencia. Sin ella todos los 
* filósofos cogen un tenedor y nadie come. 
*/
void	set_philo_to_start(t_philo *philo)
{
	if (philo->id % 2 == 1 || philo->id == philo->god->n_philo - 1)
		usleep(1000);
}