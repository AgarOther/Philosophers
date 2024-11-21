/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:19:58 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/21 16:10:48 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->print_lock);
	if (philo_died(philo->data))
		return (0);
	printf(str, get_time() - philo->rules.start_time, philo->id);
	pthread_mutex_unlock(philo->print_lock);
	return (1);
}

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (!print_message(philo, TAKE_LEFT_FORK))
		return (0);
	pthread_mutex_lock(philo->right_fork);
	if (is_dead(philo))
	{
		print_message(philo, HAS_DIED);
		philo->is_alive = false;
		return (0);
	}
	if (!print_message(philo, TAKE_RIGHT_FORK))
		return (0);
	if (!print_message(philo, IS_EATING))
		return (0);
	usleep(philo->rules.eat_time * 1000);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (!print_message(philo, FINISHED_EATING))
		return (0);
	if (!print_message(philo, IS_SLEEPING))
		return (0);
	usleep(philo->rules.sleep_time * 1000);
	return (print_message(philo, IS_THINKING));
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->id % 2)
		usleep(5000);
	while (1)
	{
		if (!philo_eat(philo))
			return (NULL);
	}
}
