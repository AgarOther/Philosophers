/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:03:41 by scraeyme          #+#    #+#             */
/*   Updated: 2026/02/27 11:57:14 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <sys/wait.h>

void	join_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rules.philo_count)
	{
		waitpid(data->philos->pid, 0, 0);
		i++;
	}
}

void	free_data(t_data *data)
{
	if (data->philos)
	{
		sem_close(data->forks);
		sem_unlink("/forks");
		sem_close(data->sem_print);
		sem_unlink("/sem_print");
	}
	free(data->philos);
	return ;
}
