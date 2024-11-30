/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:06:44 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/30 13:47:18 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_mutex_unlock(philo->status_lock);
	return (is_dead);
}

void	philoop(t_data *data, int i, int j, int announce)
{
	while (!is_philo_dead(&data->philos[i]) && j < data->rules->philo_count)
	{
		j = (j + 1) * is_philo_done(&data->philos[i]);
		i = (i + 1) % data->rules->philo_count;
		usleep(50);
	}
	pthread_mutex_lock(&data->print_lock);
	i = -1;
	if (j == data->rules->philo_count)
		printf(ALL_FULL, get_time() - data->rules->start_time);
	while (++i < data->rules->philo_count)
	{
		pthread_mutex_lock(data->philos[i].status_lock);
		if (!announce && data->philos[i].is_dead == 1)
			announce = data->philos[i].id;
		data->philos[i].is_dead = 2;
		pthread_mutex_unlock(data->philos[i].status_lock);
	}
	pthread_mutex_unlock(&data->print_lock);
	if (announce)
		print_message(&data->philos[announce - 1], HAS_DIED, 0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
	{
		printf("\033[31;1mYou need either 4 or 5 arguments.\033[0m\n");
		return (0);
	}
	data = get_data(argc, argv);
	if (!data)
		return (0);
	philoop(data, 0, 0, 0);
	join_all(data);
	free_data(data);
}
