/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:55:49 by seungryk          #+#    #+#             */
/*   Updated: 2024/07/21 13:42:57 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_error(t_rules *rules, int i)
{
	partial_destroy_mutex(rules, i);
	free(rules->mutex.forks);
	return (-1);
}

int	init_mutex2(t_rules *rules, int i)
{
	if (pthread_mutex_init(&(rules->mutex.die), NULL) != 0)
		return (mutex_error(rules, i));
	if (pthread_mutex_init(&rules->mutex.m_start, NULL) != 0)
	{
		pthread_mutex_destroy(&(rules->mutex.die));
		return (mutex_error(rules, i));
	}
	if (pthread_mutex_init(&rules->mutex.print, NULL) != 0)
	{
		pthread_mutex_destroy(&(rules->mutex.die));
		pthread_mutex_destroy(&(rules->mutex.m_start));
		return (mutex_error(rules, i));
	}
	return (0);
}

int	init_mutex(t_rules *rules, int num)
{
	int		i;

	i = 0;
	rules->mutex.forks = malloc(sizeof(pthread_mutex_t) * num);
	if (rules->mutex.forks == NULL)
		return (-1);
	while (i < num)
	{
		if (pthread_mutex_init(&(rules->mutex.forks[i]), NULL) != 0 || \
			pthread_mutex_init(&rules->philo[i].m_meal, NULL) != 0 || \
			pthread_mutex_init(&rules->philo[i].last_meal, NULL) != 0)
			return (mutex_error(rules, i));
		i++;
	}
	if (init_mutex2(rules, i) == -1)
		return (-1);
	return (0);
}

int	init_philo(t_rules *rules)
{
	rules->philo = malloc(sizeof(t_philo) * rules->num_of_philo);
	if (rules->philo == NULL)
	{
		free(rules->forks);
		return (-1);
	}
	memset(rules->philo, 0, sizeof(t_philo) * rules->num_of_philo);
	return (0);
}

int	init_rules(t_rules *rules, char **argv, int argc)
{
	memset(rules, 0, sizeof(*rules));
	if (check_num(rules, argc, argv) == -1)
		return (-1);
	if (argc == 6)
	{
		rules->minimum_meal = ft_atoi(argv[5]);
		if (rules->minimum_meal <= 0)
			return (-1);
	}
	if (rules->num_of_philo <= 0 || rules->time_to_die <= 0 \
		|| rules->time_to_eat < 0 || rules->time_to_sleep < 0)
		return (-1);
	rules->forks = malloc(sizeof(int) * rules->num_of_philo);
	if (!rules->forks)
		return (-1);
	memset(rules->forks, 0, sizeof(*rules->forks));
	if (init_philo(rules) == -1)
		return (-1);
	if (init_mutex(rules, rules->num_of_philo) == -1)
	{
		free(rules->forks);
		free(rules->philo);
		return (-1);
	}
	return (0);
}
