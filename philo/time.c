/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:41:27 by davifern          #+#    #+#             */
/*   Updated: 2024/03/15 16:11:09 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
* Return the diference between the time now and the startime
*/
long long	get_time(long long start)
{
	long long		time_now;
	struct timeval	now;

	gettimeofday(&now, NULL);
	time_now = now.tv_sec * 1000 + now.tv_usec / 1000;
	return (time_now - start);
}

/*
* Returns the current time in miliseconds
*/
long long	get_current_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

/*
* Fazemos nossa função de sleep porque usleep espera o tempo 
* e mais um pouquinho. Ex: você pede para dormir 100ms 
* (usleep(100*1000)) e ele dorme 102ms. 
* Acrescentamos um usleep(100) no loop para não sobrecarregar 
* o processador neste loop infinito. Então dizemos: calcule 
* o if e espere 100us, depois calcule e espere e então o 
* processador pode fazer outra coisa. Ao invés de:
* calcule, calcule, calcule infinitamente.
* usleep(10): é evitar que imprima algo depois de morto
*/
void	ft_sleep(long long time)
{
	long long	limit_time;

	limit_time = get_current_time() + time;
	while (1)
	{
		if (get_current_time() >= limit_time)
			break ;
		usleep(50);
	}
}
