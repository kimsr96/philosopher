/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:05:12 by seungryk          #+#    #+#             */
/*   Updated: 2024/07/22 15:04:26 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_dead(t_rules *rules)
{
	pthread_mutex_lock(&rules->mutex.die);
	rules->check_die = 1;
	pthread_mutex_unlock(&rules->mutex.die);
}

static int	check_min_meal(t_rules *rules)
{
	int		i;
	int		num;
	t_philo	*philo;

	i = 0;
	num = rules->num_of_philo;
	philo = rules->philo;
	while (i < num)
	{
		pthread_mutex_lock(&philo[i].m_meal);
		if (philo[i].num_meal < rules->minimum_meal)
		{
			pthread_mutex_unlock(&philo[i].m_meal);
			return (1);
		}
		pthread_mutex_unlock(&philo[i].m_meal);
		i++;
	}
	return (0);
}

int	time_to_die(t_rules *rules, t_philo *philo)
{		
	uint64_t	now;
	uint64_t	last_eat;

	now = get_time() - rules->begin_time;
	pthread_mutex_lock(&philo->last_meal);
	last_eat = philo->last_eat_time - rules->begin_time;
	if (now - last_eat > (uint64_t)rules->time_to_die)
	{
		pthread_mutex_unlock(&philo->last_meal);
		set_dead(rules);
		pthread_mutex_lock(&rules->mutex.print);
		usleep(100);
		printf("%llu %d died\n", get_time() - rules->begin_time, philo->id + 1);
		pthread_mutex_unlock(&rules->mutex.print);
		return (1);
	}
	pthread_mutex_unlock(&philo->last_meal);
	return (0);
}

int	check_philo_eat_time(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->num_of_philo)
	{
		if (time_to_die(rules, &rules->philo[i]))
			return (1);
		i++;
	}
	return (0);
}

void	*monitoring(void *arg)
{
	t_rules		*rules;

	rules = (t_rules *)arg;
	while (!is_dead(rules))
	{
		if (check_philo_eat_time(rules))
			break ;
		if (rules->minimum_meal > 0)
		{
			if (!check_min_meal(rules))
			{
				set_dead(rules);
				pthread_mutex_lock(&rules->mutex.print);
				printf("Finish eating\n");
				pthread_mutex_unlock(&rules->mutex.print);
				break ;
			}
		}
		usleep(100);
	}
	return (NULL);
}
