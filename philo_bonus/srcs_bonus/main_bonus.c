/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:06:44 by scraeyme          #+#    #+#             */
/*   Updated: 2026/02/27 12:06:56 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_philo_done(t_philo *philo)
{
	int	is_done;

	if (philo->rules.meals_goal == -1)
		return (0);
	// status lock
	is_done = philo->rules.meals_goal == philo->meals;
	// status unlock
	return (is_done);
}

int	is_philo_dead(t_philo *philo)
{
	int	is_dead;

	// status lock
	if (philo->is_dead != 2)
		philo->is_dead = time_passed(philo);
	is_dead = philo->is_dead;
	// status unlock
	return (is_dead);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc < 5 || argc > 6)
	{
		printf("\033[31;1mYou need either 4 or 5 arguments.\033[0m\n");
		return (0);
	}
	data = get_data(argc, argv);
	if (data.rules.error)
		return (1);
	i = 0;
	get_philos(&data, &i);
	if (!data.philos || i != data.rules.philo_count)
	{
		printf("\033[31;1mError allocating philosophers.\033[0m\n");
		free_data(&data);
		return (1);
	}
	join_all(&data);
	free_data(&data);
}
