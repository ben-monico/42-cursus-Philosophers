/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:21:18 by bcarreir          #+#    #+#             */
/*   Updated: 2022/07/29 22:00:15 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		usleep(500);
	while (1)
	{
		if (death_check(philo, 0))
			return (NULL);
		pthread_mutex_lock(&philo->mtx[philo->left]);
		ft_print_msg(philo, "has taken a left fork");
		if (death_check(philo, 1))
			return (NULL);
		pthread_mutex_lock(&philo->mtx[philo->right]);
		ft_print_msg(philo, "has taken a right fork");
		if (death_check(philo, 2))
			return (NULL);
		ft_eat(philo);
		pthread_mutex_unlock(&(philo->mtx[philo->right]));
		pthread_mutex_unlock(&(philo->mtx[philo->left]));
		if (philo->times_eaten >= philo->args->nbr_of_meals ||
			death_check(philo, 0))
			return (NULL);
		usleep(philo->args->sleep_dur  * 1000);
		ft_print_msg(philo, "is sleeping");
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