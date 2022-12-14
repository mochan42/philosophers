/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:44:44 by mochan            #+#    #+#             */
/*   Updated: 2022/09/12 14:20:34 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (1)
	{
		if (philo->philo_id % 2)
			usleep(1000);
		pthread_mutex_lock(&philo->exit_flag_mutex);
		if (philo->exit_flag == 1)
		{
			pthread_mutex_unlock(&philo->exit_flag_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->exit_flag_mutex);
		pthread_mutex_lock(&philo->right_fork->mutex);
		pthread_mutex_lock(&philo->left_fork->mutex);
		take_forks(philo);
		eating(philo);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	create_threads(t_prgm *vars, pthread_t *thread)
{
	int	i;

	i = 0;
	while (i < vars->nb_of_philos)
	{
		if (pthread_create(&vars->philos[i].thread, NULL, &routine,
				&vars->philos[i]) != 0)
			perror("Failed to create thread.\n");
		i++;
	}
	if (pthread_create(thread, NULL, &death_routine, vars) != 0)
		perror("Failed to create death supervisor thread.\n");
}

void	join_threads(t_prgm *vars, pthread_t *thread)
{
	int	i;

	i = 0;
	while (i < vars->nb_of_philos)
	{
		if (pthread_join(vars->philos[i].thread, NULL) != 0)
			perror("Failed to join thread");
		i++;
	}
	if (pthread_join(*thread, NULL) != 0)
		perror("Failed to join thread");
}

int	main(int argc, char **argv)
{
	t_prgm			philo_prgm;
	pthread_t		death_routine[1];

	philo_prgm.argc = argc;
	philo_prgm.argv = argv;
	if (check_input(&philo_prgm) == 1)
		return (0);
	philo_prgm.philos = malloc(sizeof(t_philo) * philo_prgm.nb_of_philos);
	if (!philo_prgm.philos)
		return (0);
	philo_prgm.array_forks = malloc(sizeof(t_fork)
			* philo_prgm.nb_of_philos);
	if (!philo_prgm.array_forks)
		return (0);
	philo_prgm.start_time = get_time_ms();
	initialize(&philo_prgm);
	create_threads(&philo_prgm, death_routine);
	join_threads(&philo_prgm, death_routine);
	destroy_mutexes(philo_prgm);
	free(philo_prgm.philos);
	free(philo_prgm.array_forks);
	return (0);
}
