/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:44:44 by mochan            #+#    #+#             */
/*   Updated: 2022/09/05 13:25:15 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	printf("%d is eating\n", philo->philo_id);
	printf("%d is sleeping\n", philo->philo_id);
	printf("%d is thinking\n", philo->philo_id);
	return (NULL);
}

void	create_threads(t_prgm *vars)
{
	int			i;

	i = 1;
	while (i <= vars->nb_of_philos)
	{
		if (pthread_create(&vars->philos[i]->thread, NULL, &routine,
				vars->philos[i]) != 0)
			perror("Failed to create thread");
		i++;
	}
}

void	join_threads(t_prgm *vars)
{
	int			i;

	i = 1;
	while (i <= vars->nb_of_philos)
	{
		if (pthread_join(vars->philos[i]->thread, NULL) != 0)
			perror("Failed to join thread");
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_prgm		philo;

	philo.argc = argc;
	philo.argv = argv;
	check_input(&philo);
	initialize(&philo);
	create_threads(&philo);
	join_threads(&philo);
	return (0);
}
