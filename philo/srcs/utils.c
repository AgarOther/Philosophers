/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:39:24 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/28 00:44:02 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	warn_user(int warn_code, t_rules *rules)
{
	if (warn_code == 1)
	{
		printf("\033[33;1mWarning! Only one philosopher specified.\n");
		printf("They WILL die!\n");
	}
	else if (warn_code == 2)
		printf("\033[33;1mWarning! Death time too low (< 60ms).\n");
	else if (warn_code == 3)
		printf("\033[33;1mWarning! Eat time too low (< 60ms).\n");
	else if (warn_code == 4)
		printf("\033[33;1mWarning! Sleep time too low (< 60ms).\n");
	else if (warn_code == 5)
		printf("\033[33;1mWarning! Too many Philosophers (> 200).\n");
	if (warn_code > 1)
		printf("Undefined behavior may occur.\n");
	printf("Starting in 3 seconds...\033[0m\n");
	usleep(3 * 1000 * 1000);
	rules->start_time = get_time();
}

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

void	join_all(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->rules->philo_count)
	{
		if (data->philos[i].thread)
			pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
