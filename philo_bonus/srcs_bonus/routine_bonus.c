/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:25:38 by scraeyme          #+#    #+#             */
/*   Updated: 2026/02/27 11:53:12 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_message(t_philo *philo, char *str, int check)
{
	sem_wait(philo->sem_print);
	if (check && is_philo_dead(philo))
	{
		sem_post(philo->sem_print);
		return ;
	}
	printf(str, get_time() - philo->rules.start_time, philo->id);
	sem_post(philo->sem_print);
}

static int	unlock_forks(t_philo *philo)
{
	sem_post(philo->forks);
	sem_post(philo->forks);
	return (0);
}

static int	philo_eats(t_philo *philo)
{
	sem_wait(philo->forks);
	print_message(philo, TAKE_FORK, 1);
	sem_wait(philo->forks);
	print_message(philo, TAKE_FORK, 1);
	print_message(philo, IS_EATING, 1);
	if (!philo_sleep(philo, philo->rules.eat_time))
		return (unlock_forks(philo));
	philo->meals++;
	philo->last_meal = get_time();
	if (is_philo_done(philo) || is_philo_dead(philo))
		return (unlock_forks(philo));
	unlock_forks(philo);
	print_message(philo, IS_SLEEPING, 1);
	usleep(500);
	if (!philo_sleep(philo, philo->rules.sleep_time))
		return (0);
	print_message(philo, IS_THINKING, 1);
	return (1);
}

static void	kill_philo(t_philo *philo)
{
	sem_wait(philo->sem_print);
	printf(DIED, get_time() - philo->rules.start_time, philo->id);
	sem_post(philo->sem_death);
}

void	routine(t_philo *philo)
{
	if (philo->rules.philo_count == 1)
	{
		print_message(philo, TAKE_FORK, 0);
		usleep(philo->rules.death_time * 1000);
		printf(DIED, get_time() - philo->rules.start_time, philo->id);
		sem_post(philo->sem_death);
		return ;
	}
	if (philo->id % 2 == 0)
		usleep(1000000);
	philo->last_meal = get_time();
	while (1)
	{
		if (!philo_eats(philo))
		{
			if (is_philo_dead(philo))
				kill_philo(philo);
			else
				sem_post(philo->sem_end);
			break ;
		}
	}
	return ;
}
