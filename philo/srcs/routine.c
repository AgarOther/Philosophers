/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:25:38 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/26 13:28:15 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *str, int check)
{
	pthread_mutex_lock(philo->print_lock);
	if (check && is_philo_dead(philo))
	{
		pthread_mutex_unlock(philo->print_lock);
		return ;
	}
	printf(str, get_time() - philo->rules.start_time, philo->id);
	pthread_mutex_unlock(philo->print_lock);
}

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
	if (philo->is_dead != 2)
		philo->is_dead = time_passed(philo);
	is_dead = philo->is_dead;
	if (is_dead == 1)
		print_message(philo, HAS_DIED, 0);
	pthread_mutex_unlock(philo->status_lock);
	return (is_dead);
}

int	philo_eats(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, TAKE_LEFT_FORK, 1);
	pthread_mutex_lock(philo->right_fork);
	if (is_philo_done(philo) || is_philo_dead(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	print_message(philo, TAKE_RIGHT_FORK, 1);
	print_message(philo, IS_EATING, 1);
	philo_sleep(philo->rules.eat_time);
	philo->meals++;
	philo->last_meal = get_time();
	if (is_philo_done(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_message(philo, IS_SLEEPING, 1);
	philo_sleep(philo->rules.sleep_time);
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
		philo_sleep(philo->rules.death_time);
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
