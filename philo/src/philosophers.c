/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:44:44 by mochan            #+#    #+#             */
/*   Updated: 2022/09/10 13:16:34 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	usleep(500);
	if (philo->philo_id % 2)
		usleep(1000);
	while (1)
	{
		// pthread_mutex_unlock(&philo->exit_flag_mutex);
		pthread_mutex_lock(&philo->right_fork->mutex);
		// pthread_mutex_lock(&philo->exit_flag_mutex);
		if (philo->philo_exit_flag == 0)
			take_a_fork(philo);
		// pthread_mutex_unlock(&philo->exit_flag_mutex);
		pthread_mutex_lock(&philo->left_fork->mutex);
		// pthread_mutex_lock(&philo->exit_flag_mutex);
		if (philo->philo_exit_flag == 0)
			take_a_fork(philo);
		// pthread_mutex_unlock(&philo->exit_flag_mutex);
		// pthread_mutex_lock(&philo->exit_flag_mutex);
		if (philo->philo_exit_flag == 0)
			eating(philo);
		// pthread_mutex_unlock(&philo->exit_flag_mutex);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		// pthread_mutex_lock(&philo->exit_flag_mutex);
		if (philo->philo_exit_flag == 0)
			sleeping(philo);
		// pthread_mutex_unlock(&philo->exit_flag_mutex);
		// pthread_mutex_lock(&philo->exit_flag_mutex);
		if (philo->philo_exit_flag == 0)
			thinking(philo);
		// pthread_mutex_unlock(&philo->exit_flag_mutex);
		// pthread_mutex_lock(&philo->exit_flag_mutex);
		if (philo->philo_exit_flag == 1)
		{
			// pthread_mutex_unlock(&philo->exit_flag_mutex);
			break;
		}
		// pthread_mutex_unlock(&philo->exit_flag_mutex);
	}
	return (NULL);
}

void	*death_check(void *arg)
{
	t_prgm		*vars;
	int			i;
	int			flag_alive;
	int			j;

	vars = (t_prgm *) arg;
	while (1)
	{
		i = 0;
		while (i < vars->nb_of_philos)
		{
			pthread_mutex_lock(&vars->philos[i].exit_flag_mutex);
			pthread_mutex_lock(&vars->philos[i].last_meal_mutex);
			flag_alive = get_time_ms() - vars->philos[i].last_meal_time;
			if (flag_alive >= vars->philos[i].ttd)
			{
				vars->exit_flag = 1;
				j = 0;
				while (j < vars->nb_of_philos)
				{
					vars->philos[j].philo_exit_flag = 1;
					j++;
				}
				break;
			}
			pthread_mutex_unlock(&vars->philos[i].last_meal_mutex);
			pthread_mutex_unlock(&vars->philos[i].exit_flag_mutex);
			i++;
		}
		if (vars->exit_flag == 1)
		{
			printf("%10ld philo %d died\n",
				get_time_ms() - vars->philos[i].start_time,
				vars->philos[i].philo_id);
			break;
		}
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
			perror("Failed to create thread.\n");
		i++;
	}
	if (pthread_create(&vars->death_supervisor, NULL, &death_check, vars) != 0)
		perror("Failed to create death supervisor thread.\n");
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
	if (pthread_join(vars->death_supervisor, NULL) != 0)
		perror("Failed to join thread");
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
	philo_prgm.array_forks = malloc(sizeof(t_fork)
			* philo_prgm.nb_of_philos);
	if (!philo_prgm.array_forks)
		return (0);
	initialize(&philo_prgm);
	create_threads(&philo_prgm);
	join_threads(&philo_prgm);
	destroy_mutexes(philo_prgm);
	return (0);
}
