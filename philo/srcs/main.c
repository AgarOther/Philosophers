/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:17:40 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/19 20:44:43 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 4 || argc > 6)
		return (ft_putendl("Error! Please specify between 4-5 arguments.", 1));
	data = get_data(argc, argv);
	if (!data)
		return (ft_putendl("Error! Please specify integer values > 0.", 2));
	print_philos(data);
	sleep(12);
	join_all(data);
	free_all(data);
}
