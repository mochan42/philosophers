/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:44:44 by mochan            #+#    #+#             */
/*   Updated: 2022/09/07 16:25:29 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	// time_t	instant_ttrf;
	// time_t	instant_ttlf;
	// time_t	instant_tte;
	// time_t	instant;
	time_t	time;
	
	philo = (t_philo *) arg;
	if (philo->philo_id % 2)
		sleep(3);
	pthread_mutex_lock(philo->right_fork);
	time = get_time_ms();
	printf("%10ld %d has taken a fork\n", time - philo->start_time, philo->philo_id);
	pthread_mutex_lock(philo->left_fork);
	time = get_time_ms();
	printf("%10ld %d has taken a fork\n", time - philo->start_time, philo->philo_id);
	time = get_time_ms();
	printf("%10ld %d is eating\n", time - philo->start_time, philo->philo_id);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	// printf("%d is sleeping\n", philo->philo_id);
	// printf("%d is thinking\n", philo->philo_id);
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
	philo_prgm.array_forks = malloc(sizeof(pthread_mutex_t) * philo_prgm.nb_of_philos);
	if (!philo_prgm.array_forks)
		return (0);
	initialize(&philo_prgm);
	create_threads(&philo_prgm);
	join_threads(&philo_prgm);
	return (0);
}
