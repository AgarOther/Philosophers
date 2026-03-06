/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:03:41 by scraeyme          #+#    #+#             */
/*   Updated: 2026/02/27 11:25:22 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void	free_mutex(pthread_mutex_t	*forks, int size)
{
	int	i;

	if (!forks)
		return ;
	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
	return ;
}

void	free_data(t_data *data)
{
	if (data->philos)
		free_mutex(data->status_lock, data->rules.philo_count);
	free_mutex(data->forks, data->rules.philo_count);
	pthread_mutex_destroy(&data->print_lock);
	free(data->philos);
	return ;
}
