/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:06:14 by scraeyme          #+#    #+#             */
/*   Updated: 2026/02/27 11:25:16 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define TAKE_LEFT_FORK "[%lld ms] Philo #%d has taken their left fork! 🔱\n"
# define TAKE_RIGHT_FORK "[%lld ms] Philo #%d has taken their right fork! 🔱\n"
# define IS_EATING "[%lld ms] Philo #%d is eating! 🍝\n"
# define FINISHED_EATING "[%lld ms] Philo #%d has finished eating! 🍽️\n"
# define IS_SLEEPING "[%lld ms] Philo #%d is sleeping! 💤\n"
# define IS_THINKING "[%lld ms] Philo #%d is thinking! 💭\n"
# define DIED "[%lld ms] Philo #%d died! 💀\n"
# define ALL_FULL "[%lld ms] All philosophers are full! 🫃\n"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_rules
{
	int			philo_count;
	int			death_time;
	int			eat_time;
	int			sleep_time;
	int			meals_goal;
	long long	start_time;
	int			error;
}				t_rules;

typedef struct s_philo
{
	int				id;
	int				is_dead;
	int				meals;
	long long		last_meal;
	t_rules			rules;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*status_lock;
}				t_philo;

typedef struct s_data
{
	t_rules			rules;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*status_lock;
	pthread_mutex_t	print_lock;
}				t_data;

typedef enum e_warning_reason
{
	SINGLE_PHILOSOPHER,
	LOW_DEATH_TIME,
	LOW_EAT_TIME,
	LOW_SLEEP_TIME,
	TOO_MANY_PHILOSOPHERS
}	t_Warning_Reason;

// Free
void			free_mutex(pthread_mutex_t	*forks, int size);
void			free_data(t_data *data);
int				unlock_forks(t_philo *philo);

// Parsing
t_data			get_data(int argc, char **argv);
pthread_mutex_t	*get_mutex(int n);
void			get_philos(t_data *data, int *i);

// Routine
void			*routine(void *param);
int				is_philo_dead(t_philo *philo);
int				is_philo_done(t_philo *philo);
void			print_message(t_philo *philo, char *str, int check);

// Utils
int				philo_sleep(t_philo *philo, int ms);
int				ft_safe_atoi(const char *nptr);
int				time_passed(t_philo *philo);
long long		get_time(void);
void			join_all(t_data *data);

// Warning
void			warning_check(t_rules rules);
void			warn_user(t_Warning_Reason warn_code);

#endif