/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:44:12 by seungryk          #+#    #+#             */
/*   Updated: 2024/07/20 13:47:09 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	partial_destroy_mutex(t_rules *rules, int i)
{
	while (i)
	{
		pthread_mutex_destroy(&rules->mutex.forks[i]);
		pthread_mutex_destroy(&rules->philo[i].m_meal);
		pthread_mutex_destroy(&rules->philo[i].last_meal);
		i--;
	}
}

int	destroy_mutex(t_rules *rules, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (pthread_mutex_destroy(&rules->mutex.forks[i]) != 0)
			return (-1);
		if (pthread_mutex_destroy(&rules->philo[i].last_meal) != 0)
			return (-1);
		if (pthread_mutex_destroy(&rules->philo[i].m_meal) != 0)
			return (-1);
		i++;
	}
	if (pthread_mutex_destroy(&rules->mutex.m_start) != 0)
		return (-1);
	if (pthread_mutex_destroy(&rules->mutex.die) != 0)
		return (-1);
	if (pthread_mutex_destroy(&rules->mutex.print) != 0)
		return (-1);
	return (0);
}

int	ft_exit(t_rules *rules)
{
	if (destroy_mutex(rules, rules->num_of_philo) == -1)
		return (-1);
	free(rules->mutex.forks);
	free(rules->philo);
	return (0);
}
