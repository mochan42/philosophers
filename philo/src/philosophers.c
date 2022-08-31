/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:44:44 by mochan            #+#    #+#             */
/*   Updated: 2022/08/31 17:49:47 by mochan           ###   ########.fr       */
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
		vars->number_of_times_each_philosopher_must_eat = ft_atoi(
				vars->argv[5]);
	else
		vars->number_of_times_each_philosopher_must_eat = 0;
}

void	*routine()
{
	printf("Hello from thread\n");
	sleep(1);
	printf("Hello again\n");
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_prgm		philo;
	pthread_t	t1;
	pthread_t	t2;
	
	philo.argc = argc;
	philo.argv = argv;
	check_input(&philo);
	initialize(&philo);
	
	pthread_create(&t1, NULL, &routine, NULL);
	pthread_create(&t2, NULL, &routine, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return (0);
}
