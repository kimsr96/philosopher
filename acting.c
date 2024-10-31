/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acting.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:07:00 by seungryk          #+#    #+#             */
/*   Updated: 2024/04/28 16:43:45 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_fork(t_philo *philo, t_rules *rules)
{
	int	num;

	num = philo->rules->num_of_philo;
	pthread_mutex_lock(&rules->mutex.forks[philo->id - 1]);
	if (print_msg(philo, rules, "has taken a fork") == -1)
		return ;
	pthread_mutex_lock(&rules->mutex.forks[philo->id % num]);
	if (print_msg(philo, rules, "has taken a fork") == -1)
		return ;
}

void	put_down_fork(t_philo *philo, t_rules *rules)
{
	int	num;

	num = rules->num_of_philo;
	pthread_mutex_unlock(&rules->mutex.forks[philo->id - 1]);
	pthread_mutex_unlock(&rules->mutex.forks[philo->id % num]);
}

void	thinking(t_philo *philo, t_rules *rules)
{
	if (print_msg(philo, rules, "is thinking") == -1)
		return ;
}

void	eating(t_philo *philo, t_rules *rules)
{
	int	num;

	num = philo->rules->num_of_philo;
	pick_up_fork(philo, rules);
	if (rules->mutex.die)
	{
		pthread_mutex_unlock(&rules->mutex.forks[philo->id]);
		pthread_mutex_unlock(&rules->mutex.forks[(philo->id % num) + 1]);
		return ;
	}
	philo->time_to_die = get_time();
	if (print_msg(philo, rules, "is eating") == -1)
		return ;
	timer(philo->rules->time_to_eat);
	put_down_fork(philo, rules);
}

void	sleeping(t_philo *philo, t_rules *rules)
{
	if (print_msg(philo, rules, "is sleeping") == -1)
		return ;
	timer(rules->time_to_sleep);
}
