/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:06:14 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/26 16:35:03 by scraeyme         ###   ########.fr       */
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
	t_rules			*rules;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*status_lock;
	pthread_mutex_t	print_lock;
}				t_data;

// Utils
void		philo_sleep(int ms);
int			ft_safe_atoi(const char *nptr);
int			time_passed(t_philo *philo);
long long	get_time(void);
void		join_all(t_data *data);

// Free
void		*free_mutex(pthread_mutex_t	*forks, int size);
void		*free_data(t_data *data);
void		unlock_forks(t_philo *philo);

// Parsing
t_data		*get_data(int argc, char **argv);

// Routine
void		*routine(void *param);
int			is_philo_dead(t_philo *philo);
int			is_philo_done(t_philo *philo);
void		print_message(t_philo *philo, char *str, int check);

#endif