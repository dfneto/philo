/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:34:11 by davifern          #+#    #+#             */
/*   Updated: 2024/03/06 13:53:12 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_god	t_god;
typedef struct s_philo
{
	int				id;
	int				times_eaten;
	long long		last_meal;
	pthread_t		th;
	pthread_mutex_t	m_last_meal;
	pthread_mutex_t	m_times_eaten;
	t_god			*god;
}	t_philo;

typedef struct s_god
{
	int				all_alive;
	int				n_times_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_philo;
	long long		start;
	pthread_mutex_t	m_print;
	pthread_mutex_t	mutex_all_alive;
	pthread_mutex_t	m_start;
	pthread_mutex_t	*mutex_fork;
	t_philo			*philo;
}	t_god;

typedef enum s_status
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_status;

/* routine.c */
void			*routine(void *philo_data);

/* utils.c */
int				exit_error(int error);
int				define_left_fork(t_philo *philo);
void			print(t_philo *philo, int status);
void			set_philo_to_start(t_philo *philo);

/* stop_conditions.c */
int				all_alive(t_god *god);
int				philosopher_died(t_philo *philo);
int				eat_enough(t_philo *philo);

/* create_destroy.c */
t_god			*create_god(char **argv);
int				create_philos(t_god *god);
int				clean_and_destroy(t_god *god);
int				wait_threads(t_god *god);

/* parser.c */
int				check_input(int argc, char **argv);
void			get_input_data(char **argv, t_god *god);

/* time.c */
long long		get_time(long long start);
long long		get_current_time(void);
void			ft_sleep(long long time);

#endif