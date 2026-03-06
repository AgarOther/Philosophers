/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:39:24 by scraeyme          #+#    #+#             */
/*   Updated: 2026/02/27 11:15:48 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

inline int	is_philo_done(t_philo *philo)
{
	return (philo->rules.meals_goal == philo->meals
		&& philo->rules.meals_goal != -1);
}

int	is_philo_dead(t_philo *philo)
{
	if (philo->is_dead != 2)
		philo->is_dead = time_passed(philo);
	return (philo->is_dead);
}

int	philo_sleep(t_philo *philo, int ms)
{
	usleep(ms * 1000);
	if (is_philo_dead(philo))
		return (0);
	return (1);
}

int	time_passed(t_philo *philo)
{
	return ((get_time() - philo->last_meal) > philo->rules.death_time);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
