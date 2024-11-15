/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:13:43 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/15 16:33:30 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h> // gettimeofday

typedef struct s_data
{
	int	forks;
	int	death_time;
	int	eat_time;
	int	sleep_time;
	int	eat_amount;
}			t_data;

int		ft_atoi(char *nptr);

#endif