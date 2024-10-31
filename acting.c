/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acting.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:07:00 by seungryk          #+#    #+#             */
/*   Updated: 2024/07/22 18:31:02 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thinking(t_philo *philo, t_rules *rules)
{
	if (print_msg(philo, rules, "is thinking"))
		return (1);
	usleep(500);
	return (0);
}

int	sleeping(t_philo *philo, t_rules *rules)
{
	if (print_msg(philo, rules, "is sleeping"))
		return (1);
	if (timer(rules, rules->time_to_sleep))
		return (1);
	return (0);
}
