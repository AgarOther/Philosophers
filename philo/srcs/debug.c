/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:57:00 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/19 20:31:21 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*debug_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *) param;
	pthread_mutex_lock(philo->print_lock);
	printf("I am Philosopher #%d!\n", philo->id);
	pthread_mutex_unlock(philo->print_lock);
	return (NULL);
}

void	print_philos(t_data *data)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = data->philos;
	while (i < data->philos_count)
	{
		printf("Philo ID: %d | Left Fork Address: %p | Right Fork Address: %p\n", i, philos[i].left_fork, philos[i].right_fork);
		i++;
	}
}
