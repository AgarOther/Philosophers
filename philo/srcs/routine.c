/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:25:38 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/25 18:11:28 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philo_done(t_philo *philo)
{
	int	is_done;

	if (philo->rules.meals_goal == -1)
		return (0);
	pthread_mutex_lock(philo->status_lock);
	is_done = philo->rules.meals_goal == philo->meals;
	pthread_mutex_unlock(philo->status_lock);
	return (is_done);
}

int	is_philo_dead(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(philo->status_lock);
	is_dead = philo->is_dead;
	pthread_mutex_unlock(philo->status_lock);
	return (is_dead);
}

void	print_message(t_philo *philo)
{
	pthread_mutex_lock(philo->print_lock);
	printf("I am Philosopher %d!\n", philo->id);
	pthread_mutex_unlock(philo->print_lock);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *) param;
	
	return (NULL);
}
