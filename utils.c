/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:48:52 by bcarreir          #+#    #+#             */
/*   Updated: 2022/07/27 22:44:45 by bcarreir         ###   ########.fr       */
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
	static unsigned long	init;

	pthread_mutex_lock(&philo->printmtx);
	if (init == 0)
	{
		gettimeofday(&t, NULL);
		init = (t.tv_sec * 1000) + (t.tv_usec / 1000); 
	}
	gettimeofday(&t, NULL);
	ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	printf("%lu ms %d %s\n", ms - init, philo->id, str);
	pthread_mutex_unlock(&philo->printmtx);
}

void	ft_eat(t_philo *philo)
{
	struct timeval	t;
	long			aux;

	gettimeofday(&t, NULL);
	philo->times_eaten++;
	aux = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	while (((t.tv_sec * 1000) + (t.tv_usec / 1000)) - aux < philo->args->eat_dur)
		gettimeofday(&t, NULL);
}