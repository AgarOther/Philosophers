/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:39:24 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/25 18:24:13 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(int ms)
{
	usleep(ms * 1000);
}

int	time_passed(t_philo *philo)
{
	return ((get_time() - philo->last_meal) > philo->rules.death_time);
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
