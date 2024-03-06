/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:01:07 by davifern          #+#    #+#             */
/*   Updated: 2024/03/06 13:59:37 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	{
		if (status == FORK)
			printf("%.5lld %d has taken a fork\n",
				get_time(philo->god->start), philo->id);
		if (status == EAT)
			printf("%.5lld %d is eating\n",
				get_time(philo->god->start), philo->id);
		if (status == SLEEP)
			printf("%.5lld %d is sleeping\n",
				get_time(philo->god->start), philo->id);
		if (status == THINK)
			printf("%.5lld %d is thinking\n",
				get_time(philo->god->start), philo->id);
		if (status == DIE)
			printf("\033[31m%.5lld %d died\033[0m\n",
				get_time(philo->god->start), philo->id);
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
	if (philo->id % 2 == 1)
		usleep(1500);
}

int	define_left_fork(t_philo *philo)
{
	if (philo->id == 0)
		return (philo->god->n_philo - 1);
	else
		return (philo->id - 1);
}

int	exit_error(int error)
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
