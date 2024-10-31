/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:22:01 by seungryk          #+#    #+#             */
/*   Updated: 2024/04/28 16:35:16 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_died(t_rules *rules, uint64_t start_time)
{
	uint64_t	now;

	now = get_time();
	if (now - start_time > (uint64_t)rules->time_to_die)
	{
		pthread_mutex_lock(&rules->mutex.mutex_die);
		print_msg(rules->philo, rules, "is died");
		rules->mutex.die = 1;
		pthread_mutex_unlock(&rules->mutex.mutex_die);
		return (0);
	}
	return (1);
}

void	*thread_f(void *arg)
{
	t_philo		*philo;
	t_rules		*rules;

	philo = (t_philo *)arg;
	rules = (t_rules *)philo->rules;
	if (philo->id % 2 == 0)
		usleep(200);
	philo->time_to_die = rules->begin_time;
	while (is_died(rules, philo->time_to_die))
	{
		thinking(philo, rules);
		eating(philo, rules);
		sleeping(philo, rules);
	}
	return (NULL);
}

int	join_thread(t_philo *philo, int cnt_philo)
{
	int	i;
	int	thr;

	i = 0;
	while (i < cnt_philo)
	{
		thr = pthread_join(philo[i].thread_id, NULL);
		if (thr != 0)
			return (-1);
		i++;
	}
	return (1);
}

int	create_thread(t_rules *rules)
{
	int		i;
	int		thr_id;
	t_philo	*philo;

	i = 0;
	philo = rules->philo;
	rules->begin_time = get_time();
	while (i < rules->num_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].rules = rules;
		thr_id = pthread_create(&(philo[i].thread_id), NULL, \
										thread_f, &philo[i]);
		if (thr_id != 0)
			return (-1);
		i++;
	}
	return (0);
}
