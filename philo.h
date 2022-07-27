/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:43:27 by bcarreir          #+#    #+#             */
/*   Updated: 2022/07/27 22:45:07 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_args
{
	int	philo_nbr;
	int	ms_til_death;
	int	eat_dur;
	int	sleep_dur;
	int	nbr_of_meals;
}	t_args;

typedef struct s_philo
{
	pthread_mutex_t *mtx;
	pthread_mutex_t printmtx;
	pthread_t tr;
	t_args *args;
	int	id;
	int	left;
	int	right;
	int	starve_time;
	int	times_eaten;
}	t_philo;

typedef struct s_global
{
	t_args *args;
	t_philo *philo;
	pthread_mutex_t *mutexes;
	pthread_mutex_t print;
}	t_global;

int	ft_atoi(const char *str);
void	ft_eat(t_philo *philo);
void	ft_print_msg(t_philo *philo, char *str);
void	ft_simulation(t_philo *philo);

#endif