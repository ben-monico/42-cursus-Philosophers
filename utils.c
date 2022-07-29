/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:48:52 by bcarreir          #+#    #+#             */
/*   Updated: 2022/07/29 22:01:57 by bcarreir         ###   ########.fr       */
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

void	ft_print_msg(t_philo *philo, char *str)
{
	struct timeval			t;
	unsigned long			ms;

	pthread_mutex_lock(&philo->printmtx);
	if (philo->args->init_ms == 0)
			ft_initms(philo);
	gettimeofday(&t, NULL);
	ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	if (philo->args->death_track)
		return ;
	printf("%lu ms - %d %s\n", ms - philo->args->init_ms, philo->id, str);
	pthread_mutex_unlock(&philo->printmtx);
}

void	ft_eat(t_philo *philo)
{
	struct timeval	t;
	unsigned long			aux;

	gettimeofday(&t, NULL);
	philo->times_eaten++;
	aux = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	ft_print_msg(philo, "is eating");
	while (((t.tv_sec * 1000) + (t.tv_usec / 1000)) - aux < (unsigned long)philo->args->eat_dur)
		gettimeofday(&t, NULL);
	philo->starve_time = aux + philo->args->eat_dur - philo->args->init_ms;
}

int	starve_check(t_philo *philo)
{	
	struct timeval	t;
	unsigned long	cur_time;

	if (philo->args->death_track == 1)
		return (1);
	gettimeofday(&t, NULL);
	cur_time = ((t.tv_sec * 1000) + (t.tv_usec / 1000));
	if ((cur_time - philo->args->init_ms) - philo->starve_time >= (unsigned long)philo->args->ms_til_death)
	{
		printf("%d has died after %lu\n", philo->id, cur_time - philo->args->init_ms - philo->starve_time);
		ft_print_msg(philo, "has starved");
		philo->args->death_track = 1;
		return (1);
	}
	// printf("%d starve ms %lu\n",philo->id, (t.tv_sec * 1000) + (t.tv_usec / 1000)  - philo->args->init_ms - philo->starve_time);
	return (0);
}

void	ft_initms(t_philo *philo)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	philo->args->init_ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	printf("%lu\n", philo->args->init_ms);
}

int	death_check(t_philo *philo, int i)
{
	if (philo->args->init_ms == 0)
		return (0);
	if (philo->args->death_track || starve_check(philo))
	{
		if (i == 1)
			pthread_mutex_unlock(&(philo->mtx[philo->left]));
		else if (i == 2)
		{
			pthread_mutex_unlock(&(philo->mtx[philo->left]));
			pthread_mutex_unlock(&(philo->mtx[philo->right]));
		}
		return (1);
	}
	else 
		return (0);
}