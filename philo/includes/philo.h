/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:06:14 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/25 14:59:07 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define TAKE_LEFT_FORK "[%lld ms] Philo #%d has taken their left fork! 🍴\n"
# define TAKE_RIGHT_FORK "[%lld ms] Philo #%d has taken their right fork! 🍴\n"
# define IS_EATING "[%lld ms] Philo #%d is eating! 🍝\n"
# define FINISHED_EATING "[%lld ms] Philo #%d has finished eating! 🍽️\n"
# define IS_SLEEPING "[%lld ms] Philo #%d is sleeping! 💤\n"
# define IS_THINKING "[%lld ms] Philo #%d is thinking! 💭\n"
# define HAS_DIED "[%lld ms] Philo #%d died! 💀\n"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_data	t_data;

typedef struct s_rules
{
	int				philo_count;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				meal_goal;
	long long		start_time;
}				t_rules;

typedef struct s_philo
{
	int				id;
	int				meals;
	long long		last_eat;
	t_rules			rules;
	t_data			*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*status_lock;
	pthread_t		thread;
}				t_philo;

struct s_data
{
	t_rules			*rules;
	t_philo			*philos;
	int				status;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	status_lock;
	pthread_mutex_t	*forks;
};

int			ft_safe_atoi(const char *nptr);
t_data		*set_data(int argc, char **argv);
void		*routine(void *param);
long long	get_time(void);
void		join_all(t_data *data);
int			status_check(t_philo *philo);
long long	time_passed(t_philo *philo);
void		philo_sleep(int ms);

#endif