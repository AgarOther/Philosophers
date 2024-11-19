/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:25:58 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/19 14:25:11 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	set_philosophers(t_data **data)
{
	int		i;
	t_data	*tmp;

	i = 0;
	tmp = *data;
	while (i < tmp->philos_count)
	{
		tmp->philos[i].id = i;
		tmp->philos[i].is_alive = true;
		tmp->philos[i].last_meal = 0;
		tmp->philos[i].times_ate = 0;
		i++;
	}
	return (true);
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
	data->philos = malloc(sizeof(t_philo) * (data->philos_count));
	if (!data->start_time || !data->philos_count || !data->death_time
		|| !data->eat_time || !data->sleep_time || !data->meals_goal
		|| !data->philos || !set_philosophers(&data))
	{
		if (data->philos)
			free(data->philos);
		free(data);
		return (NULL);
	}
	return (data);
}
