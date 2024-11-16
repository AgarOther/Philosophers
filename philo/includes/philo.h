/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:13:43 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/16 15:29:05 by scraeyme         ###   ########.fr       */
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

typedef struct s_fork	t_fork;

typedef struct s_philo
{
	int		id;
	int		meals;
	int		last_meal;
	t_fork	*left_fork;
	t_fork	*right_fork;
}				t_philo;

struct s_fork
{
	bool	is_taken;
	//mutex
};

typedef struct s_round_table
{
	t_philo		**philosophers;
	int			forks;
	int			death_time;
	int			eat_time;
	int			sleep_time;
	int			eat_amount;
	long		time_start;
}			t_round_table;

int		ft_atoi(char *nptr);
void	ft_putendl(char *str);
int		welcome_philosophers(t_round_table *data);

#endif
