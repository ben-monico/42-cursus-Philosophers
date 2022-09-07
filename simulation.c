/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:21:18 by bcarreir          #+#    #+#             */
/*   Updated: 2022/09/07 19:14:00 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_simulation(t_philo *philo)
{
	int	i;

	ft_initms(philo);
	i = -1;
	while(++i < philo->args->philo_nbr)
		pthread_create(&(philo[i].tr), NULL, routine, philo + i);
	i = -1;
	while(++i < philo->args->philo_nbr)
		pthread_join(philo[i].tr, NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		nb;

	philo = arg;
	nb = philo->args->nbr_of_meals;
	if (philo->id % 2 == 0)
		usleep(500);
	while (1)
	{
		if (philo->meals >= nb || death_check(philo, 0))
				return (NULL);
		if (ft_pickforks(philo) || ft_eat(philo) || ft_sleep(philo))
			return (NULL);
	}
}

int	ft_pickforks(t_philo *philo)
{
		pthread_mutex_lock(&philo->mtx[philo->left]);
		ft_print_msg(philo, "has taken a left fork", 0);
		if (death_check(philo, 1))
			return (1);
		pthread_mutex_lock(&philo->mtx[philo->right]);
		ft_print_msg(philo, "has taken a right fork", 0);
		return (0);
}

int	ft_eat(t_philo *philo)
{
	struct timeval			t;
	unsigned long			aux;

	if (death_check(philo, 2))
		return (1);
	gettimeofday(&t, NULL);
	philo->meals++;
	aux = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	ft_print_msg(philo, "is eating", 0);
	while (((t.tv_sec * 1000) + (t.tv_usec / 1000)) - aux
		< (unsigned long)philo->args->eat_dur)
		gettimeofday(&t, NULL);
	pthread_mutex_unlock(&(philo->mtx[philo->right]));
	pthread_mutex_unlock(&(philo->mtx[philo->left]));
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (death_check(philo, 0))
		return (1);
	ft_print_msg(philo, "is sleeping", 0);
	usleep(philo->args->sleep_dur * 1000);
	return (0);
}