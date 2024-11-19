/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:23:10 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/19 20:25:18 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_all(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philos_count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
