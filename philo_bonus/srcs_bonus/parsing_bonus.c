/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:53:12 by scraeyme          #+#    #+#             */
/*   Updated: 2026/02/27 11:10:30 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_rules	get_rules(int argc, char **argv)
{
	t_rules	rules;

	rules.philo_count = ft_safe_atoi(argv[1]);
	rules.death_time = ft_safe_atoi(argv[2]);
	rules.eat_time = ft_safe_atoi(argv[3]);
	rules.sleep_time = ft_safe_atoi(argv[4]);
	if (argc == 6)
		rules.meals_goal = ft_safe_atoi(argv[5]);
	else
		rules.meals_goal = -1;
	rules.start_time = get_time();
	if (!rules.philo_count || !rules.death_time || !rules.eat_time
		|| !rules.sleep_time || !rules.meals_goal || !rules.start_time)
	{
		printf("\033[31;1mInvalid arguments.\033[0m\n");
		rules.error = 1;
	}
	else
		rules.error = 0;
	return (rules);
}

pthread_mutex_t	*get_mutex(int n)
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
			return (NULL);
		}
		i++;
	}
	return (mutex);
}

void	get_philos(t_data *data, int *i)
{
	data->philos = malloc(sizeof(t_philo) * data->rules.philo_count);
	if (!data->philos)
		return ;
	data->status_lock = get_mutex(data->rules.philo_count + 1);
	if (!data->status_lock)
		return ;
	while (*i < data->rules.philo_count)
	{
		data->philos[*i].id = *i + 1;
		data->philos[*i].is_dead = 0;
		data->philos[*i].meals = 0;
		data->philos[*i].last_meal = get_time();
		data->philos[*i].rules = data->rules;
		data->philos[*i].left_fork = &data->forks[(*i + 1)
			% data->rules.philo_count];
		data->philos[*i].right_fork = &data->forks[*i];
		data->philos[*i].print_lock = &data->print_lock;
		data->philos[*i].status_lock = &data->status_lock[*i];
		if (pthread_create(&data->philos[*i].thread, NULL,
				routine, &data->philos[*i]))
			return ;
		*i += 1;
	}
}

t_data	get_data(int argc, char **argv)
{
	t_data	data;

	data.rules = get_rules(argc, argv);
	if (data.rules.error)
		return (data);
	warning_check(data.rules);
	data.rules.start_time = get_time();
	return (data);
}
