/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:33:43 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/25 15:18:45 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	print_message(t_philo *philo, char *str)
{
	if (!status_check(philo))
	{
		pthread_mutex_lock(philo->print_lock);
		printf(str, get_time() - philo->rules.start_time, philo->id + 1);
		pthread_mutex_unlock(philo->print_lock);
		return (1);
	}
	return (0);
}

void	status_write(t_philo *philo, int value)
{
	pthread_mutex_lock(philo->status_lock);
	philo->data->status = value;
	pthread_mutex_unlock(philo->status_lock);
}

static int	is_dead(t_philo *philo)
{
	if (time_passed(philo) && !status_check(philo))
	{
		print_message(philo, HAS_DIED);
		status_write(philo, 1);
		return (1);
	}
	return (0);
}

static int	philo_eats(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, TAKE_LEFT_FORK);
	pthread_mutex_lock(philo->right_fork);
	if (is_dead(philo) || status_check(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	print_message(philo, TAKE_RIGHT_FORK);
	print_message(philo, IS_EATING);
	philo_sleep(philo->rules.eat_time);
	if (status_check(philo))
		return (0);
	philo->meals++;
	philo->last_eat = get_time();
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_message(philo, IS_SLEEPING);
	philo_sleep(philo->rules.sleep_time);
	if (status_check(philo))
		return (0);
	print_message(philo, IS_THINKING);
	return (1);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *) param;
	if (philo->rules.philo_count == 1)
	{
		print_message(philo, TAKE_LEFT_FORK);
		philo_sleep(philo->rules.death_time);
		print_message(philo, HAS_DIED);
		status_write(philo, 1);
		pthread_mutex_destroy(philo->right_fork);
		return (NULL);
	}
	if (philo->id % 2)
		usleep(5000);
	while (!status_check(philo))
	{
		if (!philo_eats(philo) || philo->meals == philo->rules.meal_goal)
			break ;
	}
	pthread_mutex_destroy(philo->right_fork);
	return (NULL);
}
