/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:34:11 by davifern          #+#    #+#             */
/*   Updated: 2024/02/27 11:00:49 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
#include <stdlib.h>
# include <sys/time.h>

typedef struct s_god t_god;
typedef struct s_philo
{
	int				id;
	long long		fasting;
	t_god			*god;
}   t_philo;

typedef struct s_god
{
	int				all_alive;
	int				n_times_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_philo;
	long long		start;
	t_philo			*philo;
}	t_god;

int             ft_atoi(const char *str);
int             check_input(int argc, char **argv);
int             philosopher_died(t_philo *philo);
int				all_alived(t_philo *philo);
long long		get_time(long long start);
long long		get_start_time(void);
t_god			*create_god(char **argv);
void			philosopher_die(t_philo *philo);
// unsigned long	get_current_time(struct timeval start, struct timeval now);
// long long		get_time(void);
// long long		get_time_diff(long long start, long long now);
#endif