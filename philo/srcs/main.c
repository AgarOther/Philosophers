/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:16:40 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/15 16:34:24 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_data	*get_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
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
	if (data->forks < 1 || data->death_time < 1 || data->eat_time < 1
		|| data->sleep_time < 1
		|| (data->eat_amount != -1 && data->eat_amount < 1))
	{
		free(data);
		return (NULL);
	}
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (0);
	data = get_data(argc - 1, argv);
	if (!data)
		return (0);
	printf("OK\n");
	free(data);
}
