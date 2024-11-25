/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:12:44 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/25 15:19:41 by scraeyme         ###   ########.fr       */
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
		rules->meal_goal = ft_safe_atoi(argv[5]);
	else
		rules->meal_goal = -1;
	rules->start_time = get_time();
	if (!rules->philo_count || !rules->death_time || !rules->eat_time
		|| !rules->sleep_time || !rules->meal_goal)
		return (NULL);
	return (rules);
}

int	set_philos(t_data *data, int i)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->rules->philo_count);
	while (++i < data->rules->philo_count)
	{
		if (!data->forks || pthread_mutex_init(&data->forks[i], NULL))
			return (0);
	}
	i = -1;
	data->forks = data->forks;
	while (++i < data->rules->philo_count)
	{
		data->philos[i].id = i;
		data->philos[i].meals = 0;
		data->philos[i].data = data;
		data->philos[i].last_eat = data->rules->start_time;
		data->philos[i].rules = *data->rules;
		data->philos[i].left_fork = &data->forks[(i + 1)
			% data->rules->philo_count];
		data->philos[i].right_fork = &data->forks[i];
		data->philos[i].print_lock = &data->print_lock;
		data->philos[i].status_lock = &data->status_lock;
		if (pthread_create(&data->philos[i].thread, NULL,
				routine, &data->philos[i]))
			return (0);
	}
	return (1);
}

static void	*free_all(t_data *data)
{
	free(data->rules);
	free(data);
	return (NULL);
}

t_data	*set_data(int argc, char **argv)
{
	t_rules	*rules;
	t_data	*data;

	rules = get_rules(argc, argv);
	if (!rules)
		return (NULL);
	data = malloc(sizeof(t_data));
	if (!data)
	{
		free(rules);
		return (NULL);
	}
	data->rules = rules;
	data->philos = malloc(sizeof(t_philo) * rules->philo_count);
	if (!data->philos)
		return (NULL);
	data->status = 0;
	if (pthread_mutex_init(&data->status_lock, NULL)
		|| pthread_mutex_init(&data->print_lock, NULL))
		return (NULL);
	if (!set_philos(data, -1))
		return (free_all(data));
	return (data);
}
