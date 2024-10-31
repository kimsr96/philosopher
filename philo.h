/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:05:36 by seungryk          #+#    #+#             */
/*   Updated: 2024/07/21 13:38:05 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <memory.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_rules	t_rules;

typedef struct s_philo
{
	int				id;
	int				num_meal;
	t_rules			*rules;
	pthread_t		thread_id;
	uint64_t		last_eat_time;
	pthread_mutex_t	m_meal;
	pthread_mutex_t	last_meal;
}				t_philo;

typedef struct s_mutex
{
	pthread_mutex_t	m_start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	die;
	pthread_mutex_t	print;
}				t_mutex;

typedef struct s_rules
{
	int			start;
	int			num_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			minimum_meal;
	int			check_die;
	int			*forks;
	uint64_t	begin_time;
	t_philo		*philo;
	t_mutex		mutex;
}				t_rules;

/* thread.c */
int			is_dead(t_rules *rules);
int			create_thread(t_rules *rules);
int			join_thread(t_philo *philo, int cnt_philo);
void		*thread_f(void *arg);

/* utils.c */
uint64_t	get_time(void);
int			ft_atoi(char *str);
int			check_num(t_rules *rules, int argc, char **argv);
int			timer(t_rules *rules, uint64_t time);
int			print_msg(t_philo *philo, t_rules *rules, char *str);

/* acting.c */
int			thinking(t_philo *philo, t_rules *rules);
int			sleeping(t_philo *philo, t_rules *rules);

/* eating.c */
int			eating(t_philo *philo, t_rules *rules);

/* finish.c */
void		partial_destroy_mutex(t_rules *rules, int i);
int			ft_exit(t_rules *rules);

/* init.c */
int			init_rules(t_rules *rules, char **argv, int argc);

/* monitoring.c */
void		*monitoring(void *arg);

#endif