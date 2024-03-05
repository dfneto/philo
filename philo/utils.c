/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:01:07 by davifern          #+#    #+#             */
/*   Updated: 2024/03/05 15:43:19 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_input_data(char **argv, t_god *god)
{
	god->start = 0;
	god->n_philo = ft_atoi(argv[1]);
	god->time_to_die = ft_atoi(argv[2]);
	god->time_to_eat = ft_atoi(argv[3]);
	god->time_to_sleep = ft_atoi(argv[4]);
	god->n_times_eat = -1;
	if (argv[5])
		god->n_times_eat = ft_atoi(argv[5]);
}

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
	pthread_mutex_init(&god->mutex_all_alive, NULL);
	pthread_mutex_init(&god->m_print, NULL);
	// pthread_mutex_init(&god->m_start, NULL);
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

int	clean_and_destroy(t_god *god)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&god->mutex_all_alive);
	pthread_mutex_destroy(&god->m_print);
	// pthread_mutex_destroy(&god->m_start);
	while (i < god->n_philo)
	{
		pthread_mutex_destroy(&god->mutex_fork[i]);
		pthread_mutex_destroy(&god->philo[i].m_fasting);
		i++;
	}
	//Ver se o leaks se eu comentar abaixo
	free(god->mutex_fork);
	free(god->philo);
	free(god);
	return (0);
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
	// if (philo->fasting == -1)
	// 	return (0);
	pthread_mutex_lock(&philo->m_fasting); 	//TODO: talvez o erro seja nesse mutex
	time_now = get_time(philo->god->start);
	if (time_now - philo->fasting >= philo->god->time_to_die)
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
	if (all_alive(philo->god))
	// if (philo->god->all_alive)
	{
		if (status == FORK)
			printf("%.5lld %d has taken a fork\n", get_time(philo->god->start), philo->id);
		if (status == EAT)
			printf("%.5lld %d is eating\n", get_time(philo->god->start), philo->id);
		if (status == SLEEP)
			printf("%.5lld %d is sleeping\n", get_time(philo->god->start), philo->id);
		if (status == THINK)
			printf("%.5lld %d is thinking\n", get_time(philo->god->start), philo->id);
		if (status == DIE)
			printf("\033[31m%.5lld %d died\033[0m\n", get_time(philo->god->start), philo->id);
	}
	pthread_mutex_unlock(&philo->god->m_print);
}

/*
* Los filósofos impares y el último duermen por 1ms. 
* Esta función es para tratar la concurrencia. Sin ella todos los 
* filósofos cogen un tenedor y nadie come. 
*/
void	set_philo_to_start(t_philo *philo)
{
	if (philo->id % 2 == 1)// || philo->id == philo->god->n_philo - 1)
		usleep(1500);
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

int	define_left_fork(t_philo *philo)
{
	if (philo->id == 0)
		return (philo->god->n_philo - 1);
	else
		return (philo->id - 1);
}

int	create_philos_and_start_threads(t_god *god, void *routine(void *))
{
	(void)routine;
	int			i;

	i = 0;
	while (i < god->n_philo)
	{
		god->philo[i].id = i;
		god->philo[i].times_eaten = 0;
		god->philo[i].god = god;
		god->philo[i].fasting = get_time(god->start);
		pthread_mutex_init(&god->philo[i].m_fasting, NULL);
		// if (pthread_create(&god->philo[i].th, NULL, routine, &god->philo[i])) //começa a thread
			// return (3);
		// god->philo[i].fasting = get_time(god->start);
		// table->philos[i].last_meal = timestamp(); O Aitor e Sebas fazem depois de criar a thread
		i++;
	}
	return (0);
}

int	exit_error(int	error)
{
	if (error == 1)
		printf("Input error\n");
	if (error == 2)
		printf("Malloc error\n");
	if (error == 3)
		printf("Thread creation error\n");
	if (error == 4)
		printf("Thread join error\n");
	return (0);
}