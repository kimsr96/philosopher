/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:02:29 by seungryk          #+#    #+#             */
/*   Updated: 2024/04/28 16:17:25 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_rules *rules, int num)
{
	int		i;
	int		ret;

	i = 0;
	rules->mutex.forks = malloc(sizeof(pthread_mutex_t) * num);
	if (rules->mutex.forks == NULL)
		return (-1);
	rules->mutex.is_occupy = malloc(sizeof(char) * num);
	if (rules->mutex.is_occupy == NULL)
		return (-1);
	while (i < num)
	{
		ret = pthread_mutex_init(&(rules->mutex.forks[i]), NULL);
		if (ret != 0)
			return (-1);
		rules->mutex.is_occupy[i] = '0';
		i++;
	}
	pthread_mutex_init(&(rules->mutex.mutex_die), NULL);
	pthread_mutex_init(&(rules->mutex.print), NULL);
	rules->mutex.die = 0;
	return (0);
}

int	init_rules(t_rules *rules, char **argv)
{
	memset(rules, 0, sizeof(*rules));
	rules->num_of_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->philo = malloc(sizeof(t_philo) * rules->num_of_philo);
	if (rules->philo == NULL)
		return (-1);
	if (init_mutex(rules, rules->num_of_philo) == -1)
		return (-1);
	return (0);
}

int	destroy_mutex(t_rules *rules, int num)
{
	int	i;
	int	ret;

	i = 0;
	while (i < num)
	{
		ret = pthread_mutex_destroy(&(rules->mutex.forks[i]));
		if (ret != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc != 5)
		return (0);
	if (init_rules(&rules, argv) == -1)
		return (0);
	if (create_thread(&rules) == -1)
		return (0);
	if (join_thread(rules.philo, rules.num_of_philo) == -1)
		return (0);
	if (destroy_mutex(&rules, rules.num_of_philo) == -1)
		return (0);
	free(rules.mutex.forks);
	free(rules.philo);
	return (0);
}
