/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:44:44 by mochan            #+#    #+#             */
/*   Updated: 2022/08/31 16:17:42 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	initialize(t_prgm *vars)
{
	vars->number_of_philosophers = ft_atoi(vars->argv[1]);
	vars->time_to_die = ft_atoi(vars->argv[2]);
	vars->time_to_eat = ft_atoi(vars->argv[3]);
	vars->time_to_sleep = ft_atoi(vars->argv[4]);
	if (vars->argc == 6)
		vars->number_of_times_each_philosopher_must_eat =
			ft_atoi(vars->argv[5]);
	else
		vars->number_of_times_each_philosopher_must_eat = 0;
}

int	main(int argc, char **argv)
{
	t_prgm	philo;

	philo.argc = argc;
	philo.argv = argv;
	check_input(&philo);
	initialize(&philo);
	return (0);
}
