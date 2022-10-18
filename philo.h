/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:43:27 by bcarreir          #+#    #+#             */
/*   Updated: 2022/10/18 15:05:44 by bcarreir         ###   ########.fr       */
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
	unsigned long	init_ms;
	int				philo_nbr;
	int				starve_time;
	int				eat_dur;
	int				sleep_dur;
	int				nbr_of_meals;
	int				death_track;
}	t_args;

typedef struct s_philo
{
	pthread_mutex_t	*mtx;
	pthread_mutex_t	*printmtx;
	pthread_mutex_t	*death_mtx;
	pthread_mutex_t	*arr_mtx;
	int				*arr;
	pthread_t		tr;
	t_args			*args;
	int				id;
	int				left;
	int				right;
	long			lastmeal_ms;
	int				meals;
}	t_philo;

typedef struct s_global
{
	pthread_mutex_t	*mutexes;
	pthread_mutex_t	*print;
	pthread_mutex_t	*deathmtx;
	pthread_mutex_t	*arrmtx;
	t_philo			*philo;
	t_args			*args;
	int				*arr;
}	t_global;

int		ft_atoi(const char *str);
int		ft_eat(t_philo *philo);
int		death_check(t_philo *philo, int i);
void	free_all(t_global *g);
void	ft_initms(t_philo *philo);
int		ft_pickforks(t_philo *philo);
void	ft_print_msg(t_philo *philo, char *str);
int		ft_timeleft(t_philo *philo);
void	*routine(void *arg);
void	ft_simulation(t_philo *philo);
int		ft_sleep(t_philo *philo);
int		starve_check(t_philo *philo);

#endif