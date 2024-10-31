/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:23:29 by seungryk          #+#    #+#             */
/*   Updated: 2024/07/22 15:15:26 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_num(t_rules *rules, int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] < '0' || argv[i][j] > '9') && argv[i][j] != '+')
				return (-1);
			j++;
		}
		i++;
	}
	rules->num_of_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	return (0);
}

int	ft_atoi(char *str)
{
	long long	num;
	long long	temp;
	int			idx;
	int			sign;

	num = 0;
	idx = 0;
	sign = 1;
	while ((str[idx] >= 9 && str[idx] <= 13) || str[idx] == 32)
		idx++;
	if (str[idx] == '+' || str[idx] == '-')
	{
		if (str[idx] == '-')
			sign *= -1;
		idx++;
	}
	while (str[idx] && (str[idx] >= '0' && str[idx] <= '9'))
	{
		temp = num * 10 + (str[idx] - '0');
		if (temp < num)
			return (-1 + (sign < 0));
		num = temp;
		idx++;
	}
	return (num * sign);
}

int	print_msg(t_philo *philo, t_rules *rules, char *str)
{
	uint64_t	time;

	pthread_mutex_lock(&rules->mutex.print);
	if (is_dead(rules))
	{
		pthread_mutex_unlock(&rules->mutex.print);
		return (1);
	}
	time = get_time() - rules->begin_time;
	printf("%llu %d %s\n", time, philo->id + 1, str);
	pthread_mutex_unlock(&rules->mutex.print);
	return (0);
}

int	timer(t_rules *rules, uint64_t time)
{
	uint64_t	start;

	start = get_time();
	while (start + time > get_time())
	{
		if (is_dead(rules))
			return (1);
		usleep(200);
	}
	return (0);
}

uint64_t	get_time(void)
{
	struct timeval	tv;
	uint64_t		time_ms;

	gettimeofday(&tv, NULL);
	time_ms = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (time_ms);
}
