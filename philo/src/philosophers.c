/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:44:44 by mochan            #+#    #+#             */
/*   Updated: 2022/09/08 13:09:51 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->philo_id % 2)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(philo->right_fork);
		take_a_fork(philo);
		pthread_mutex_lock(philo->left_fork);
		take_a_fork(philo);
		eating(philo);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	create_threads(t_prgm *vars)
{
	int	i;

	i = 0;
	while (i < vars->nb_of_philos)
	{
		if (pthread_create(&vars->philos[i].thread, NULL, &routine,
				&vars->philos[i]) != 0)
			perror("Failed to create thread");
		i++;
	}
}

void	join_threads(t_prgm *vars)
{
	int	i;

	i = 0;
	while (i < vars->nb_of_philos)
	{
		if (pthread_join(vars->philos[i].thread, NULL) != 0)
			perror("Failed to join thread");
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_prgm		philo_prgm;

	philo_prgm.start_time = get_time_ms();
	philo_prgm.argc = argc;
	philo_prgm.argv = argv;
	check_input(&philo_prgm);
	philo_prgm.philos = malloc(sizeof(t_philo) * philo_prgm.nb_of_philos);
	if (!philo_prgm.philos)
		return (0);
	philo_prgm.array_forks = malloc(sizeof(pthread_mutex_t)
			* philo_prgm.nb_of_philos);
	if (!philo_prgm.array_forks)
		return (0);
	initialize(&philo_prgm);
	create_threads(&philo_prgm);
	join_threads(&philo_prgm);
	return (0);
}
