/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:52:37 by seungryk          #+#    #+#             */
/*   Updated: 2024/07/22 18:35:03 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	pick_one_fork(t_rules *rules, t_philo *philo, int idx)
{
	while (1)
	{
		if (is_dead(rules))
			return (1);
		pthread_mutex_lock(&rules->mutex.forks[idx]);
		if (rules->forks[idx] == 0)
		{
			rules->forks[idx] = 1;
			pthread_mutex_unlock(&rules->mutex.forks[idx]);
			break ;
		}
		pthread_mutex_unlock(&rules->mutex.forks[idx]);
		usleep(100);
	}
	if (print_msg(philo, rules, "has taken a fork"))
		return (1);
	return (0);
}

static int	pick_up_fork(t_rules *rules, t_philo *philo, int num)
{
	int	first;
	int	second;

	if ((rules->time_to_eat != rules->time_to_sleep) || \
		(rules->time_to_eat == rules->time_to_sleep && (philo->id + 1) % num))
	{
		first = philo->id;
		second = (philo->id + 1) % num;
	}
	else
	{
		first = (philo->id + 1) % num;
		second = philo->id;
	}
	if (pick_one_fork(rules, philo, first))
		return (1);
	if (pick_one_fork(rules, philo, second))
		return (1);
	return (0);
}

static int	put_down_fork(t_philo *philo, t_rules *rules, int num)
{
	pthread_mutex_lock(&rules->mutex.forks[philo->id]);
	rules->forks[philo->id] = 0;
	pthread_mutex_unlock(&rules->mutex.forks[philo->id]);
	pthread_mutex_lock(&rules->mutex.forks[(philo->id + 1) % num]);
	rules->forks[(philo->id + 1) % num] = 0;
	pthread_mutex_unlock(&rules->mutex.forks[(philo->id + 1) % num]);
	return (0);
}

int	eating(t_philo *philo, t_rules *rules)
{
	int	num;

	num = philo->rules->num_of_philo;
	if (is_dead(rules))
		return (1);
	if (pick_up_fork(rules, philo, num))
		return (1);
	pthread_mutex_lock(&philo->last_meal);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&philo->last_meal);
	if (print_msg(philo, rules, "is eating"))
		return (1);
	if (timer(rules, rules->time_to_eat))
	{
		put_down_fork(philo, rules, num);
		return (1);
	}
	put_down_fork(philo, rules, num);
	pthread_mutex_lock(&philo->m_meal);
	philo->num_meal++;
	pthread_mutex_unlock(&philo->m_meal);
	return (0);
}
