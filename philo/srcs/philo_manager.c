/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:23:10 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/21 15:54:24 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_dead(t_philo *philo)
{
	if (time_passed(philo))
		return (true);
	return (false);
}

bool	philo_died(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		if (!data->philos[i].is_alive)
			return (true);
		i++;
	}
	return (false);
}

int	death_loop(t_data *data)
{
	while (!philo_died(data))
		usleep(1000);
	return (1);
}

void	join_all(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philos_count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
