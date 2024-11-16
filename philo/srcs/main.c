/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:16:40 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/16 15:48:33 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
	{
		ft_putendl("[Error] Couldn't get starting time.");
		return (0);
	}
	return (tv.tv_usec / 1000 + tv.tv_sec * 1000);
}

static t_round_table	*get_table(int argc, char **argv)
{
	t_round_table	*data;

	data = malloc(sizeof(t_round_table));
	if (!data)
		return (NULL);
	data->forks = ft_atoi(argv[1]);
	data->death_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	if (argc == 5)
		data->eat_amount = ft_atoi(argv[5]);
	else
		data->eat_amount = -1;
	data->time_start = get_time();
	if (data->forks < 1 || data->death_time < 1 || data->eat_time < 1
		|| data->sleep_time < 1
		|| (data->eat_amount != -1 && data->eat_amount < 1)
		|| data->time_start <= 0)
	{
		free(data);
		return (NULL);
	}
	return (data);
}

int	main(int argc, char **argv)
{
	t_round_table	*table;
	pthread_t		thread1;

	if (argc < 5 || argc > 6)
		return (0);
	table = get_table(argc - 1, argv);
	if (!table)
		return (1);
	free(table);
	printf("OK\n");
}
