/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:25:58 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/21 16:02:03 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_rules	rules_copy(t_rules *rules)
{
	t_rules	rulescpy;

	rulescpy.death_time = rules->death_time;
	rulescpy.eat_time = rules->eat_time;
	rulescpy.death_time = rules->sleep_time;
	rulescpy.start_time = rules->start_time;
	return (rulescpy);
}

t_rules	*set_rules(int argc, char **argv)
{
	t_rules	*rules;

	rules = malloc(sizeof(t_rules));
	if (!rules)
		return (NULL);
	rules->death_time = ft_atol(argv[2]);
	rules->eat_time = ft_atol(argv[3]);
	rules->sleep_time = ft_atol(argv[4]);
	if (argc == 6)
		rules->meals_goal = ft_atol(argv[5]);
	else
		rules->meals_goal = -1;
	rules->start_time = get_time();
	return (rules);
}

static bool	populate_table(t_data **data, int i)
{
	t_data	*tmp;

	tmp = *data;
	while (++i < tmp->philos_count)
	{
		if (pthread_mutex_init(&tmp->forks[i], NULL) != 0)
			return (false);
	}
	i = -1;
	while (++i < tmp->philos_count)
	{
		tmp->philos[i].id = i + 1;
		tmp->philos[i].is_alive = true;
		tmp->philos[i].times_ate = 0;
		tmp->philos[i].last_meal = get_time();
		tmp->philos[i].left_fork = &tmp->forks[(i + 1) % tmp->philos_count];
		tmp->philos[i].right_fork = &tmp->forks[i];
		tmp->philos[i].print_lock = &tmp->print_lock;
		tmp->philos[i].rules = rules_copy(tmp->rules);
		tmp->philos[i].data = *data;
		if (pthread_create(&tmp->philos[i].thread, NULL,
				routine, &tmp->philos[i]))
			return (false);
	}
	return (true);
}

void	*free_all(t_data *data)
{
	int	i;

	i = 0;
	if (data->philos)
		free(data->philos);
	if (data->forks)
	{
		while (i < data->philos_count)
			pthread_mutex_destroy(&data->forks[i++]);
		free(data->forks);
	}
	free(data->rules);
	free(data);
	return (NULL);
}

t_data	*get_data(int argc, char **argv)
{
	t_data	*data;
	t_rules	*rules;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	rules = set_rules(argc, argv);
	if (!rules)
		return (NULL);
	data->philos_count = ft_atol(argv[1]);
	data->philos = malloc(sizeof(t_philo) * (data->philos_count));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philos_count);
	data->rules = rules;
	if (!rules->start_time || !data->philos_count || !rules->death_time
		|| !rules->eat_time || !rules->sleep_time || !rules->meals_goal
		|| !data->philos || pthread_mutex_init(&data->print_lock, NULL) != 0
		|| !populate_table(&data, -1))
		return (free_all(data));
	return (data);
}
