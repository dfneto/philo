/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:34:11 by davifern          #+#    #+#             */
/*   Updated: 2024/02/23 11:40:19 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>

int             ft_atoi(const char *str);
int             check_input(int argc, char **argv);
unsigned long	get_current_time(struct timeval start, struct timeval now);
#endif