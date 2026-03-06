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

int	philo_sleep(t_philo *philo, int ms)
{
	int	i;

	i = 0;
	while (i < ms)
	{
		if (ms - i >= 50)
			usleep(50 * 1000);
		else
			usleep((ms - i) * 1000);
		i += 50;
		if (is_philo_dead(philo))
			return (0);
	}
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

