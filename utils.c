/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:23:29 by seungryk          #+#    #+#             */
/*   Updated: 2024/04/28 16:25:59 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	int			id;
	uint64_t	time;

	id = philo->id;
	pthread_mutex_lock(&(rules->mutex.print));
	time = get_time() - rules->begin_time;
	printf("%llu %d %s\n", time, id, str);
	pthread_mutex_unlock(&(rules->mutex.print));
	return (0);
}

void	timer(uint64_t time)
{
	uint64_t	start;
	uint64_t	now;
	uint64_t	gap;

	start = get_time();
	while (1)
	{
		now = get_time();
		gap = now - start;
		if (gap > time)
			break ;
	}
}

uint64_t	get_time(void)
{
	struct timeval	tv;
	uint64_t		time_ms;

	gettimeofday(&tv, NULL);
	time_ms = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (time_ms);
}
