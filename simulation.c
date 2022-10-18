/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:21:18 by bcarreir          #+#    #+#             */
/*   Updated: 2022/10/18 17:33:59 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_simulation(t_philo *philo)
{
	int	i;

	ft_initms(philo);
	i = -1;
	while (++i < philo->args->philo_nbr)
		pthread_create(&(philo[i].tr), NULL, routine, philo + i);
	i = -1;
	while (++i < philo->args->philo_nbr)
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
	if (ft_singlephilo(philo))
		return (NULL);
	while (1)
	{
		if ((philo->meals >= nb && nb != -1))
			return (NULL);
		if (ft_pickforks(philo) || ft_eat(philo) || ft_sleep(philo))
			return (NULL);
	}
}

int	ft_singlephilo(t_philo *philo)
{
	if (philo->left == philo->right)
	{
		pthread_mutex_lock(&philo->mtx[philo->left]);
		philo->arr[philo->left] = 1;
		ft_print_msg(philo, "has taken a left fork");
		usleep(1000 * philo->args->starve_time);
		death_check(philo, 0);
		return (1);
	}
	return (0);
}
