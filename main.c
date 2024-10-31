/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:02:29 by seungryk          #+#    #+#             */
/*   Updated: 2024/07/22 15:04:16 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_monitoring(t_rules *rules)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, &monitoring, rules) != 0)
		return (-1);
	if (pthread_join(monitor_thread, NULL) != 0)
		return (-1);
	return (0);
}

int	create_thread(t_rules *rules)
{
	int			i;
	t_philo		*philo;

	i = -1;
	philo = rules->philo;
	while (++i < rules->num_of_philo)
	{
		philo[i].id = i;
		philo[i].rules = rules;
		if (pthread_create \
				(&(philo[i].thread_id), NULL, thread_f, &philo[i]) != 0)
			return (-1);
		usleep(100);
	}
	pthread_mutex_lock(&rules->mutex.m_start);
	i = -1;
	rules->start = 1;
	rules->begin_time = get_time();
	while (++i < rules->num_of_philo)
		philo[i].last_eat_time = rules->begin_time;
	pthread_mutex_unlock(&rules->mutex.m_start);
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc != 5 && argc != 6)
		return (1);
	if (init_rules(&rules, argv, argc) == -1)
		return (1);
	if (create_thread(&rules) == -1)
	{
		ft_exit(&rules);
		return (1);
	}
	if (start_monitoring(&rules) == -1)
		return (1);
	if (join_thread((&rules)->philo, rules.num_of_philo) == -1)
		return (1);
	ft_exit(&rules);
	return (0);
}
