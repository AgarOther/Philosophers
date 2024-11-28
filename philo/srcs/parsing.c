/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:53:12 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/28 12:55:04 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_rules	*get_rules(int argc, char **argv)
{
	t_rules	*rules;

	rules = malloc(sizeof(t_rules));
	if (!rules)
		return (NULL);
	rules->philo_count = ft_safe_atoi(argv[1]);
	rules->death_time = ft_safe_atoi(argv[2]);
	rules->eat_time = ft_safe_atoi(argv[3]);
	rules->sleep_time = ft_safe_atoi(argv[4]);
	if (argc == 6)
		rules->meals_goal = ft_safe_atoi(argv[5]);
	else
		rules->meals_goal = -1;
	rules->start_time = get_time();
	if (!rules->philo_count || !rules->death_time || !rules->eat_time
		|| !rules->sleep_time || !rules->meals_goal || !rules->start_time)
	{
		free(rules);
		printf("\033[31;1mInvalid arguments.\033[0m\n");
		return (NULL);
	}
	return (rules);
}

static pthread_mutex_t	*get_mutex(int n)
{
	int				i;
	pthread_mutex_t	*mutex;

	i = 0;
	mutex = malloc(sizeof(pthread_mutex_t) * n);
	if (!mutex)
		return (NULL);
	while (i < n)
	{
		if (pthread_mutex_init(&mutex[i], NULL))
		{
			free_mutex(mutex, i);
			free(mutex);
			return (NULL);
		}
		i++;
	}
	return (mutex);
}

static t_philo	*get_philos(t_data *data, int i)
{
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * data->rules->philo_count);
	if (!philos)
		return (NULL);
	data->status_lock = get_mutex(data->rules->philo_count + 1);
	if (!data->status_lock)
		return (NULL);
	while (i < data->rules->philo_count)
	{
		philos[i].id = i + 1;
		philos[i].is_dead = 0;
		philos[i].meals = 0;
		philos[i].last_meal = get_time();
		philos[i].rules = *data->rules;
		philos[i].left_fork = &data->forks[(i + 1) % data->rules->philo_count];
		philos[i].right_fork = &data->forks[i];
		philos[i].print_lock = &data->print_lock;
		philos[i].status_lock = &data->status_lock[i];
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]))
			return (NULL);
		i++;
	}
	return (philos);
}

static void	warning_check(t_rules *rules)
{
	if (rules->philo_count == 1)
		warn_user(1, rules);
	else if (rules->death_time < 60)
		warn_user(2, rules);
	else if (rules->eat_time < 60)
		warn_user(3, rules);
	else if (rules->sleep_time < 60)
		warn_user(4, rules);
	if (rules->philo_count > 200)
		warn_user(5, rules);
}

t_data	*get_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->rules = get_rules(argc, argv);
	if (!data->rules)
	{
		free(data);
		return (NULL);
	}
	warning_check(data->rules);
	data->forks = get_mutex(data->rules->philo_count);
	if (!data->forks || pthread_mutex_init(&data->print_lock, NULL))
	{
		if (data->forks)
			free(data->forks);
		free(data->rules);
		free(data);
		return (NULL);
	}
	data->philos = get_philos(data, 0);
	if (!data->philos)
		return (free_data(data));
	return (data);
}
