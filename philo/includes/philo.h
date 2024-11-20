/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:13:43 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/20 17:33:21 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_rules
{
	long long		start_time;
	long long		death_time;
	long long		eat_time;
	long long		sleep_time;
	int				meals_goal;
}				t_rules;


typedef struct s_philo
{
	pthread_t		thread;
	t_rules			rules;
	int				id;
	int				times_ate;
	int				meals_goal;
	long long		start_time;
	long long		last_meal;
	bool			is_alive;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_lock;
}				t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	int				philos_count;
	t_rules			*rules;
}				t_data;

// Utility
int			ft_putendl(char *str, int ret);
long long	get_time(void);
long		ft_atol(char *nptr);
bool		time_passed(long long time1, long long time2, long long limit);

// Free
void		*free_all(t_data *data);
void		join_all(t_data *data);

// Parsing
t_data		*get_data(int argc, char **argv);

// Routine
void		*routine(void *param);

#endif
