/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:19:58 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/19 20:42:20 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *str)
{
	if (pthread_mutex_lock(philo->print_lock))
	{
		//Kill process?
	}
	printf(str, philo->id);
	if (pthread_mutex_unlock(philo->print_lock))
	{
		//Kill process?
	}
}

void	*routine(void *param)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)param;
	i = -1;
	while (++i < 5)
	{
		sleep(2);
		print_action(philo, "%d is still alive!\n");
	}
	return (NULL);
}
