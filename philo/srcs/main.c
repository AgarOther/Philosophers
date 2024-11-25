/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:06:44 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/25 15:10:37 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	status_main_check(t_data *data)
{
	int	status;

	pthread_mutex_lock(&data->status_lock);
	status = data->status;
	pthread_mutex_unlock(&data->status_lock);
	return (status);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (0);
	data = set_data(argc, argv);
	if (!data)
		return (0);
	while (!status_main_check(data))
		usleep(1000);
	join_all(data);
	pthread_mutex_destroy(&data->status_lock);
	pthread_mutex_destroy(&data->print_lock);
	free(data->rules);
	free(data->philos);
	free(data->forks);
	free(data);
}
