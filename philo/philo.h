/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:34:11 by davifern          #+#    #+#             */
/*   Updated: 2024/02/23 16:29:48 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	struct timeval start;
    struct timeval now;
	struct timeval fasting;
	int	id;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_times_eat;
}   t_philo;

// typedef struct s_god
// {
// 	struct timeval start;
// 	t_philo *philo;
// }	t_god;

int             ft_atoi(const char *str);
int             check_input(int argc, char **argv);
unsigned long	get_current_time(struct timeval start, struct timeval now);
int             philosopher_died(struct timeval fasting, struct timeval now, int time_to_die);
#endif