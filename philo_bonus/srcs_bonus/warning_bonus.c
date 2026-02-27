/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   warning_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 10:45:55 by scraeyme          #+#    #+#             */
/*   Updated: 2026/02/27 11:10:10 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	warn_user(t_Warning_Reason warn_code)
{
	int	i;

	i = 3;
	if (warn_code == SINGLE_PHILOSOPHER)
	{
		printf("\033[33;1mWarning! Only one philosopher specified.\n");
		printf("They WILL die!\n");
	}
	else if (warn_code == LOW_DEATH_TIME)
		printf("\033[33;1mWarning! Time to die too low (< 60ms).\n");
	else if (warn_code == LOW_EAT_TIME)
		printf("\033[33;1mWarning! Time to eat too low (< 60ms).\n");
	else if (warn_code == LOW_SLEEP_TIME)
		printf("\033[33;1mWarning! Time to sleep too low (< 60ms).\n");
	else if (warn_code == TOO_MANY_PHILOSOPHERS)
		printf("\033[33;1mWarning! Too many Philosophers (> 200).\n");
	if (warn_code > 1)
		printf("Undefined behavior may occur.\n");
	while (i > 0)
	{
		printf("Starting in %d seconds...\n", i);
		i--;
		usleep(1000 * 1000);
	}
	printf("\033[0m");
}

void	warning_check(t_rules rules)
{
	if (rules.philo_count == 1)
		warn_user(SINGLE_PHILOSOPHER);
	else if (rules.death_time < 60)
		warn_user(LOW_DEATH_TIME);
	else if (rules.eat_time < 60)
		warn_user(LOW_EAT_TIME);
	else if (rules.sleep_time < 60)
		warn_user(LOW_SLEEP_TIME);
	if (rules.philo_count > 200)
		warn_user(TOO_MANY_PHILOSOPHERS);
}
