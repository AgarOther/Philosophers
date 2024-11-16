/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:12:31 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/16 15:29:59 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	welcome_philosophers(t_round_table *data)
{
	t_philo	*philosophers;
	int		i;

	philosophers = malloc(data->forks * sizeof(t_philo));
	if (!philosophers)
		return (0);
	i = 1;
	while (i <= data->forks)
	{
		
	}
	return (1);
}
