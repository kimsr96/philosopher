/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:05:36 by seungryk          #+#    #+#             */
/*   Updated: 2024/04/28 16:28:02 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
 #define PHILO_H

#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_rules	t_rules;

typedef struct s_philo
{
	int				id;
	int				ready;
	t_rules			*rules;
	pthread_t		thread_id;
	uint64_t		time_to_die;
}				t_philo;

typedef struct s_mutex
{
	int				die;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	mutex_die;
	pthread_mutex_t	mutex_start;
}				t_mutex;

typedef struct s_rules
{
	int			num_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	uint64_t	begin_time;
	t_philo		*philo;
	t_mutex		mutex;
}				t_rules;


/* thread.c */
int			create_thread(t_rules *rules);
int			join_thread(t_philo *philo, int cnt_philo);
void		*thread_f(void *arg);

/* utils.c */
int			ft_atoi(char *str);
void		timer(uint64_t time);
uint64_t	get_time(void);
int			print_msg(t_philo *philo, t_rules *rules, char *str);

/* acting.c */
void		thinking(t_philo *philo, t_rules *rules);
void		eating(t_philo *philo, t_rules *rules);
void		sleeping(t_philo *philo, t_rules *rules);
#endif