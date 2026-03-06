/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:53:12 by scraeyme          #+#    #+#             */
/*   Updated: 2026/02/27 12:08:12 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_rules	get_rules(int argc, char **argv)
{
	t_rules	rules;

	rules.philo_count = ft_safe_atoi(argv[1]);
	rules.death_time = ft_safe_atoi(argv[2]);
	rules.eat_time = ft_safe_atoi(argv[3]);
	rules.sleep_time = ft_safe_atoi(argv[4]);
	if (argc == 6)
		rules.meals_goal = ft_safe_atoi(argv[5]);
	else
		rules.meals_goal = -1;
	rules.start_time = get_time();
	if (!rules.philo_count || !rules.death_time || !rules.eat_time
		|| !rules.sleep_time || !rules.meals_goal || !rules.start_time)
	{
		printf("\033[31;1mInvalid arguments.\033[0m\n");
		rules.error = 1;
	}
	else
		rules.error = 0;
	return (rules);
}

void	get_philos(t_data *data, int *i)
{
	data->philos = malloc(sizeof(t_philo) * data->rules.philo_count);
	if (!data->philos)
		return ;
	while (*i < data->rules.philo_count)
	{
		data->philos[*i].id = *i + 1;
		data->philos[*i].is_dead = 0;
		data->philos[*i].meals = 0;
		data->philos[*i].last_meal = get_time();
		data->philos[*i].rules = data->rules;
		data->philos[*i].forks = data->forks;
		data->philos[*i].sem_print = data->sem_print;
		data->philos[*i].pid = fork();
		if (data->philos[*i].pid == 0)
		{
			routine(&data->philos[*i]);
			if (data->philos[*i].meals != data->rules.meals_goal)
				print_message(&data->philos[*i], HAS_DIED, 0);
			else
				print_message(&data->philos[*i], ALL_FULL, 0);
			free_data(data);
			exit(0);
		}
		*i += 1;
	}
}

t_data	get_data(int argc, char **argv)
{
	t_data	data;

	data.rules = get_rules(argc, argv);
	if (data.rules.error)
		return (data);
	sem_unlink("/forks");
	data.forks = sem_open("/forks", O_CREAT | O_EXCL, O_RDWR, data.rules.philo_count);
	sem_unlink("/sem_print");
	data.sem_print = sem_open("/sem_print", O_CREAT | O_EXCL, O_RDWR, 1);
	if (data.forks == SEM_FAILED || data.sem_print == SEM_FAILED)
	{
		printf("\033[31;1mError opening semaphores.\033[0m\n");
		data.rules.error = 1;
		return (data);
	}
	warning_check(data.rules);
	data.rules.start_time = get_time();
	return (data);
}
