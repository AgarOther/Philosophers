/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:25:58 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/19 15:44:02 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *param)
{
	t_data	*data;

	data = (t_data *) param;
	pthread_mutex_lock(&data->print_lock);
	printf("I am a Philosopher!\n");
	pthread_mutex_unlock(&data->print_lock);
	return (NULL);
}

bool	populate_table(t_data **data)
{
	int		i;
	t_data	*tmp;

	i = 0;
	tmp = *data;
	while (i < tmp->philos_count)
	{
		if (pthread_mutex_init(&tmp->forks[i], NULL) != 0)
			return (false);
		i++;
	}
	i = 0;
	while (i < tmp->philos_count)
	{
		if (pthread_create(&tmp->philos[i].thread, NULL, routine, *data) != 0)
			return (false);
		tmp->philos[i].is_alive = true;
		tmp->philos[i].last_meal = 0;
		tmp->philos[i].times_ate = 0;
		tmp->philos[i].left_fork = &tmp->forks[(i + 1) % tmp->philos_count];
		tmp->philos[i].right_fork = &tmp->forks[i];
		i++;
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
