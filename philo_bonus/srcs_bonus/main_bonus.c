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
#include <signal.h>
#include <pthread.h>

static void	kill_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rules.philo_count)
	{
		kill(data->philos->pid, SIGKILL);
		i++;
	}
}

static void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (i < data->rules.philo_count)
	{
		sem_wait(data->sem_end);
		i++;
	}
	kill_philos(data);
	sem_post(data->sem_death);
	return (NULL);
}

static void	philoop(t_data *data)
{
	pthread_t	monitor_thread;
	int			i;

	if (pthread_create(&monitor_thread, NULL, monitor, data))
	{
		kill_philos(data);
		return ;
	}
	sem_wait(data->sem_death);
	kill_philos(data);
	i = 0;
	while (i < data->rules.philo_count)
	{
		sem_post(data->sem_end);
		i++;
	}
	pthread_join(monitor_thread, NULL);
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
	philoop(&data);
	join_all(&data);
	free_data(&data);
}
