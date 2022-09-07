/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:48:52 by bcarreir          #+#    #+#             */
/*   Updated: 2022/09/07 19:13:58 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;
	int	i;

	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && str[i] != '\0')
	{
		result = (result * 10) + str[i] - '0';
		i++;
	}
	return (result * sign);
}

void	ft_print_msg(t_philo *philo, char *str, int i)
{
	struct timeval			t;
	unsigned long			ms;

	gettimeofday(&t, NULL);
	pthread_mutex_lock(philo->printmtx);
	if (i == 4)
		return ;
	/* if (i == 0)
	{
		pthread_mutex_lock(&(philo->death_mtx));
		if (philo->args->death_track == 1)
		{
			pthread_mutex_unlock(&(philo->printmtx));
			pthread_mutex_unlock(&(philo->death_mtx));
			return ;
		}
		pthread_mutex_unlock(&(philo->death_mtx));
	} */
	ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	printf("[%lu ms] %d %s\n", ms - philo->args->init_ms, philo->id, str);
	// printf("[%lu, %d ms] %d %s\n", t.tv_sec, (int)t.tv_usec, philo->id, str);
	pthread_mutex_unlock(philo->printmtx);
}

int	starve_check(t_philo *philo)
{	
	struct timeval	t;
	unsigned long	cur;
	unsigned long	init;

	gettimeofday(&t, NULL);
	init = philo->args->init_ms;
	cur = ((t.tv_sec * 1000) + (t.tv_usec / 1000));
	if ((cur - init) - philo->starve_time
		>= (unsigned long)philo->args->ms_til_death)
	{
		philo->args->death_track = 1;
		ft_print_msg(philo, "has starved", 1);
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
		pthread_mutex_unlock(&(philo->mtx[philo->left]));
	else if (i == 2)
	{
		pthread_mutex_unlock(&(philo->mtx[philo->right]));
		pthread_mutex_unlock(&(philo->mtx[philo->left]));
	}
	pthread_mutex_unlock(philo->death_mtx);
	return (1);
}