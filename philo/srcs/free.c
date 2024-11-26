/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:03:41 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/26 16:17:30 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*free_mutex(pthread_mutex_t	*forks, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	return (NULL);
}

void	*free_data(t_data *data)
{
	free_mutex(data->forks, data->rules->philo_count);
	free_mutex(data->status_lock, data->rules->philo_count);
	free(data->rules);
	free(data->philos);
	free(data->status_lock);
	free(data->forks);
	free(data);
	return (NULL);
}
