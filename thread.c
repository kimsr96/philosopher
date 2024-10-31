/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:22:01 by seungryk          #+#    #+#             */
/*   Updated: 2024/07/22 14:04:43 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_rules *rules)
{
	pthread_mutex_lock(&rules->mutex.die);
	if (rules->check_die)
	{
		pthread_mutex_unlock(&rules->mutex.die);
		return (1);
	}
	pthread_mutex_unlock(&rules->mutex.die);
	return (0);
}

int	is_full(t_rules *rules, t_philo *philo)
{
	int	full;

	full = 0;
	pthread_mutex_lock(&philo->m_meal);
	if (philo->num_meal >= rules->minimum_meal)
		full = 1;
	pthread_mutex_unlock(&philo->m_meal);
	return (full);
}

void	*thread_f(void *arg)
{
	t_philo		*philo;
	t_rules		*rules;

	philo = (t_philo *)arg;
	rules = (t_rules *)philo->rules;
	pthread_mutex_lock(&rules->mutex.m_start);
	while (!rules->start)
	{
		pthread_mutex_unlock(&rules->mutex.m_start);
		usleep(100);
		pthread_mutex_lock(&rules->mutex.m_start);
	}
	pthread_mutex_unlock(&rules->mutex.m_start);
	if ((philo->id + 1) % 2 == 1)
		usleep(2000);
	while (!is_dead(rules))
	{
		if (eating(philo, rules))
			break ;
		if (sleeping(philo, rules))
			break ;
		if (thinking(philo, rules))
			break ;
	}
	return (NULL);
}

int	join_thread(t_philo *philo, int cnt_philo)
{
	int	i;

	i = 0;
	while (i < cnt_philo)
	{
		if (pthread_join(philo[i].thread_id, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}
