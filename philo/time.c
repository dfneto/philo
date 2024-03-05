/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:41:27 by davifern          #+#    #+#             */
/*   Updated: 2024/03/05 14:41:32 by davifern         ###   ########.fr       */
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
	// printf("Start time: %lld, Now: %lld, time_now - start: %lld\n", start, time_now, (time_now - start));
	return (time_now - start);
}

/*
* Returns the current time in miliseconds
*/
long long	get_current_time(void)
{
	long long		time_now;
	struct timeval	now;

	gettimeofday(&now, NULL);
	time_now = now.tv_sec * 1000 + now.tv_usec / 1000;
	// printf("Start time: %lld\n", time_now);
	return (time_now);
}
