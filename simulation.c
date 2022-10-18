/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:21:18 by bcarreir          #+#    #+#             */
/*   Updated: 2022/10/04 18:21:04 by bcarreir         ###   ########.fr       */
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
	while (1)
	{
		if ((philo->meals >= nb && nb != -1))
			return (NULL);
		if (ft_pickforks(philo) || ft_eat(philo) || ft_sleep(philo))
			return (NULL);
	}
}

int	ft_pickforks(t_philo *philo)
{
	while (1)
	{
		if (death_check(philo, 0))
			return (1);
		pthread_mutex_lock(philo->arr_mtx);
		if (philo->arr[philo->left] == 0 && philo->arr[philo->right] == 0)
		{
			pthread_mutex_lock(&philo->mtx[philo->left]);
			philo->arr[philo->left] = 1;
			ft_print_msg(philo, "has taken a left fork", 0);
			if (philo->left == philo->right)
			{
				pthread_mutex_unlock(philo->arr_mtx);
				usleep(1000 * philo->args->starve_time);
				if (death_check(philo, 1))
					return (1);
			}
			pthread_mutex_lock(&philo->mtx[philo->right]);
			philo->arr[philo->right] = 1;
			ft_print_msg(philo, "has taken a right fork", 0);
			pthread_mutex_unlock(philo->arr_mtx);
			return (0);
		}
		else
			pthread_mutex_unlock(philo->arr_mtx);
	}
}

int	ft_eat(t_philo *philo)
{
	struct timeval	t;
	unsigned long	aux;
	int				meal_dur;
	int				ret;

	if (death_check(philo, 2))
		return (1);
	meal_dur = philo->args->eat_dur;
	gettimeofday(&t, NULL);
	ft_print_msg(philo, "is eating", 0);
	philo->meals++;
	aux = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	philo->lastmeal_ms = aux - philo->args->init_ms;
	ret = ft_timeleft(philo);
	if (ret > 0 && ret < meal_dur)
		meal_dur = ret;
	while (((t.tv_sec * 1000) + (t.tv_usec / 1000)) - aux
		< (unsigned long)meal_dur)
		gettimeofday(&t, NULL);
	pthread_mutex_unlock(&(philo->mtx[philo->right]));
	philo->arr[philo->right] = 0;
	pthread_mutex_unlock(&(philo->mtx[philo->left]));
	philo->arr[philo->left] = 0;
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	int	ret;
	int	sleeptm;

	if (death_check(philo, 0))
		return (1);
	sleeptm = philo->args->sleep_dur;
	ret = ft_timeleft(philo);
	if (ret > 0 && ret < sleeptm)
		sleeptm = ret;
	else if (ret < 0)
		death_check(philo, 0);
	ft_print_msg(philo, "is sleeping", 0);
	usleep(sleeptm * 1000);
	return (0);
}
