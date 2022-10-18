/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:31:41 by bcarreir          #+#    #+#             */
/*   Updated: 2022/10/18 17:46:34 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	starve_check(t_philo *philo)
{	
	struct timeval	t;
	unsigned long	cur;
	unsigned long	init;

	gettimeofday(&t, NULL);
	init = philo->args->init_ms;
	cur = ((t.tv_sec * 1000) + (t.tv_usec / 1000));
	if ((cur - init) - philo->lastmeal_ms
		>= (unsigned long)philo->args->starve_time)
	{
		philo->args->death_track = 1;
		ft_print_msg(philo, "has died");
		return (1);
	}
	return (0);
}

int	death_check(t_philo *philo, int i)
{
	pthread_mutex_lock(philo->death_mtx);
	if (philo->args->death_track == 0 && starve_check(philo) == 0)
	{
		pthread_mutex_unlock(philo->death_mtx);
		return (0);
	}
	if (i == 1)
	{
		pthread_mutex_unlock(&(philo->mtx[philo->left]));
		philo->arr[philo->left] = 0;
	}
	else if (i == 2)
	{
		pthread_mutex_unlock(&(philo->mtx[philo->right]));
		philo->arr[philo->right] = 0;
		pthread_mutex_unlock(&(philo->mtx[philo->left]));
		philo->arr[philo->left] = 0;
	}
	pthread_mutex_unlock(philo->death_mtx);
	return (1);
}

int	ft_timeleft(t_philo *philo)
{
	struct timeval	t;
	unsigned long	cur;
	unsigned long	init;

	gettimeofday(&t, NULL);
	init = philo->args->init_ms;
	cur = ((t.tv_sec * 1000) + (t.tv_usec / 1000));
	return (philo->args->starve_time - (int)(cur - init) - philo->lastmeal_ms);
}
