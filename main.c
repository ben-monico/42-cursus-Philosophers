/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarreir <bcarreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:53:38 by bcarreir          #+#    #+#             */
/*   Updated: 2022/07/27 21:13:17 by bcarreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_all(t_global *g)
{
	int	i;

	pthread_mutex_init(&(g->print), NULL);
	g->mutexes = malloc(sizeof(pthread_mutex_t) * g->args->philo_nbr);
	if (!g->mutexes)
		return (1);
	i = -1;
	while (++i < g->args->philo_nbr)
		pthread_mutex_init(&(g->mutexes[i]), NULL);
	pthread_mutex_init(&g->print, NULL);
	g->philo = malloc(sizeof(t_philo) * g->args->philo_nbr);
	if (!g->philo)
		return (1);
	i = -1;
	while (++i < g->args->philo_nbr)
	{
		g->philo[i].args = g->args;
		g->philo[i].printmtx = g->print;
		g->philo[i].mtx = g->mutexes;
		g->philo[i].id = i + 1;
		g->philo[i].left = i;
		g->philo[i].right = i + 1;
		if (i == (g->args->philo_nbr - 1))
			g->philo[i].right = 0;
		g->philo[i].starve_time = -1;
		g->philo[i].times_eaten = 0;
	}
	return (0);
}

int	parse_args(t_global *g, int ac, char **av)
{
	g->args->philo_nbr = ft_atoi(av[1]);
	g->args->ms_til_death = ft_atoi(av[2]);
	g->args->eat_dur = ft_atoi(av[3]);
	g->args->sleep_dur = ft_atoi(av[4]);
	g->args->nbr_of_meals = 0;	
	if (ac == 6)
	{
		g->args->nbr_of_meals = ft_atoi(av[5]);
		if (g->args->nbr_of_meals <= 0)
			return (1);
	}	
	return (0);
}

int main(int ac, char **av)
{
	t_global g;

	if (ac < 5 || ac > 6)
		return (1);
	g.args = malloc(sizeof(t_args));
	if (!g.args)
		return (1);
	if (parse_args(&g, ac, av))
		return (1);
	if (init_all(&g))
		return (1);
	ft_simulation(g.philo);
}