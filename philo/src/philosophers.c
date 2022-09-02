/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:44:44 by mochan            #+#    #+#             */
/*   Updated: 2022/09/02 22:16:30 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	initialize(t_prgm *vars)
{
	vars->nb_of_philos = ft_atoi(vars->argv[1]);
	vars->time_to_die = ft_atoi(vars->argv[2]);
	vars->time_to_eat = ft_atoi(vars->argv[3]);
	vars->time_to_sleep = ft_atoi(vars->argv[4]);
	if (vars->argc == 6)
		vars->number_must_eat = ft_atoi(
				vars->argv[5]);
	else
		vars->number_must_eat = 0;
}

void	*routine(void *arg)
{
	int	index;

	index = *(int *) arg;
	printf("philo %d\n", index);
	free(arg);
	return (NULL);
}

void	create_threads(t_prgm *vars)
{
	pthread_t	*ph;
	int			i;
	int			*a;

	ph = malloc(sizeof(pthread_t) * (vars->nb_of_philos));
	i = 1;
	while (i <= vars->nb_of_philos)
	{
		a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&ph[i], NULL, &routine, a) != 0)
			perror("Failed to create thread");
		i++;
	}
	i = 1;
	while (i <= vars->nb_of_philos)
	{
		if (pthread_join(ph[i], NULL) != 0)
			perror("Failed to join thread");
		i++;
	}
	free(ph);
}

int	main(int argc, char **argv)
{
	t_prgm		philo;

	philo.argc = argc;
	philo.argv = argv;
	check_input(&philo);
	initialize(&philo);
	create_threads(&philo);
	return (0);
}
