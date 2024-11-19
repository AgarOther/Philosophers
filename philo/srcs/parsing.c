/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:25:58 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/19 20:40:44 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	populate_table(t_data **data)
{
	int		i;
	t_data	*tmp;

	i = -1;
	tmp = *data;
	while (++i < tmp->philos_count)
	{
		if (pthread_mutex_init(&tmp->forks[i], NULL) != 0)
			return (false);
	}
	i = -1;
	while (++i < tmp->philos_count)
	{
		tmp->philos[i].id = i;
		tmp->philos[i].is_alive = true;
		tmp->philos[i].meals_goal = tmp->meals_goal;
		tmp->philos[i].times_ate = 0;
		tmp->philos[i].left_fork = &tmp->forks[(i + 1) % tmp->philos_count];
		tmp->philos[i].right_fork = &tmp->forks[i];
		tmp->philos[i].print_lock = &tmp->print_lock;
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
	free(data);
	return (NULL);
}

t_data	*get_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->start_time = get_time();
	data->philos_count = ft_atol(argv[1]);
	data->death_time = ft_atol(argv[2]);
	data->eat_time = ft_atol(argv[3]);
	data->sleep_time = ft_atol(argv[4]);
	if (argc == 6)
		data->meals_goal = ft_atol(argv[5]);
	else
		data->meals_goal = -1;
	data->philos = NULL;
	data->forks = NULL;
	data->philos = malloc(sizeof(t_philo) * (data->philos_count));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philos_count);
	if (!data->start_time || !data->philos_count || !data->death_time
		|| !data->eat_time || !data->sleep_time || !data->meals_goal
		|| !data->philos || pthread_mutex_init(&data->print_lock, NULL) != 0
		|| !populate_table(&data))
		return (free_all(data));
	return (data);
}
