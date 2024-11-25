/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:39:24 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/25 15:09:49 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(int ms)
{
	usleep(ms * 1000);
}

long long	time_passed(t_philo *philo)
{
	return ((get_time() - philo->last_eat) > philo->rules.death_time);
}

int	status_check(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(philo->status_lock);
	status = philo->data->status;
	pthread_mutex_unlock(philo->status_lock);
	return (status);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	join_all(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->rules->philo_count)
	{
		if (data->philos[i].thread)
			pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
