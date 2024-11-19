/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:13:43 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/19 15:39:04 by scraeyme         ###   ########.fr       */
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

typedef struct s_philo
{
	pthread_t		thread;
	int				times_ate;
	int				last_meal;
	bool			is_alive;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}				t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	long long		start_time;
	int				philos_count;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				meals_goal;
}				t_data;

// Utility
int			ft_putendl(char *str, int ret);
long long	get_time(void);
long		ft_atol(char *nptr);

// Free
void		*free_all(t_data *data);
void		join_all(t_data *data);

// Parsing
t_data		*get_data(int argc, char **argv);

// Debug
void		print_philos(t_data *data);

#endif
