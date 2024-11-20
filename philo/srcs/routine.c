/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:19:58 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/20 17:32:57 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*print_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->print_lock);
	printf(str, philo->id);
	pthread_mutex_unlock(philo->print_lock);
	return (NULL);
}

bool	is_dead(t_philo *philo)
{
	if (time_passed(get_time(), philo->last_meal, philo->rules.death_time))
		return (true);
	return (false);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (1)
	{
		if (is_dead(philo))
			return (print_message(philo, "Philo #%d has died!\n"));
		usleep(1000);
	}
}
