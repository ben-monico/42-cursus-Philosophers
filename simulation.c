/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:21:18 by bcarreir          #+#    #+#             */
/*   Updated: 2022/07/27 22:55:12 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		if (philo->times_eaten >= philo->args->nbr_of_meals)
			return (NULL);
		printf("\n");
		pthread_mutex_lock(&philo->mtx[philo->left]);
		ft_print_msg(philo, "has taken a fork");
		pthread_mutex_lock(&philo->mtx[philo->right]);
		ft_print_msg(philo, "has taken a fork");
		ft_eat(philo);
		ft_print_msg(philo, "is eating");
		pthread_mutex_unlock(&(philo->mtx[philo->left]));
		pthread_mutex_unlock(&(philo->mtx[philo->right]));
		usleep(philo->args->sleep_dur  * 1000);
	}
}

void	ft_simulation(t_philo *philo)
{
	int	i;

	i = -1;
	while(++i < philo->args->philo_nbr)
		pthread_create(&(philo[i].tr), NULL, routine, philo + i);
	i = -1;
	while(++i < philo->args->philo_nbr)
		pthread_join(philo[i].tr, NULL);
}