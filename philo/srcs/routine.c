/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:25:38 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/27 12:28:28 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	lock_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, TAKE_LEFT_FORK, 1);
		pthread_mutex_lock(philo->right_fork);
		if (is_philo_done(philo) || is_philo_dead(philo))
			return (unlock_forks(philo));
		print_message(philo, TAKE_RIGHT_FORK, 1);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, TAKE_RIGHT_FORK, 1);
		pthread_mutex_lock(philo->left_fork);
		if (is_philo_done(philo) || is_philo_dead(philo))
			return (unlock_forks(philo));
		print_message(philo, TAKE_LEFT_FORK, 1);
	}
	return (1);
}

void	print_message(t_philo *philo, char *str, int check)
{
	usleep(1000);
	pthread_mutex_lock(philo->print_lock);
	if (check && is_philo_dead(philo))
	{
		pthread_mutex_unlock(philo->print_lock);
		return ;
	}
	printf(str, get_time() - philo->rules.start_time, philo->id);
	pthread_mutex_unlock(philo->print_lock);
}

void	philo_finished_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->status_lock);
	philo->meals++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->status_lock);
}

int	philo_eats(t_philo *philo)
{
	if (!lock_forks(philo))
		return (0);
	print_message(philo, IS_EATING, 1);
	if (!philo_sleep(philo, philo->rules.eat_time))
	{
		unlock_forks(philo);
		return (0);
	}
	philo_finished_eating(philo);
	if (is_philo_done(philo))
	{
		unlock_forks(philo);
		return (0);
	}
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	usleep(1000);
	print_message(philo, IS_SLEEPING, 1);
	if (!philo_sleep(philo, philo->rules.sleep_time))
		return (0);
	print_message(philo, IS_THINKING, 1);
	return (1);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *) param;
	if (philo->rules.philo_count == 1)
	{
		print_message(philo, TAKE_LEFT_FORK, 0);
		usleep(philo->rules.death_time * 1000);
		return (NULL);
	}
	if (philo->id % 2)
		usleep(15000);
	while (1)
	{
		if (is_philo_dead(philo) || !philo_eats(philo))
			break ;
	}
	return (NULL);
}
